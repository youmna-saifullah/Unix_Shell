#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "shell.h" //



GtkWidget *output_display;
GtkWidget *cmd_input;

void run_custom_shell_logic(char *input) {
    if (input == NULL || strlen(input) == 0 || input[0] == '\n') return;

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_display));
    GtkTextIter end;

    // Output capture setup
    char *temp_file = "gui_output.tmp";
    int stdout_fd = dup(STDOUT_FILENO);
    int fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    
    if (fd < 0) return;

    dup2(fd, STDOUT_FILENO);
    
    // Safety check for parsing
    char **args = split_line(input);
    if (args != NULL && args[0] != NULL) {
        execute_args(args);
    }
    
    fflush(stdout);
    dup2(stdout_fd, STDOUT_FILENO);
    close(fd);
    close(stdout_fd);

    // Show output in GUI
    FILE *fp = fopen(temp_file, "r");
    if (fp) {
        char line[1024];
        while (fgets(line, sizeof(line), fp)) {
            gtk_text_buffer_get_end_iter(buffer, &end);
            gtk_text_buffer_insert(buffer, &end, line, -1);
        }
        fclose(fp);
    }
    
    if (args) free(args);
}

// Side buttons logic fix
void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));
    
    if (strcmp(label, "CLEAR") == 0) {
        GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_display));
        gtk_text_buffer_set_text(buf, "", -1);
    } 
    else if (strcmp(label, "RM") == 0 || strcmp(label, "MKDIR") == 0 || strcmp(label, "CAT") == 0) {
        // In commands ko filename chahye hota hai, isliye user ko batayein
        GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(output_display));
        gtk_text_buffer_insert_at_cursor(buf, "\nError: Please type filename in the box and click 'Run'\n", -1);
    }
    else {
        char cmd[50];
        strcpy(cmd, label);
        for(int i = 0; cmd[i]; i++) cmd[i] = tolower(cmd[i]);
        run_custom_shell_logic(cmd);
    }
}

// GUI setup function (main) yahan same rahega...

void on_run_action(GtkWidget *widget, gpointer data) {
    char *input = (char *)gtk_entry_get_text(GTK_ENTRY(cmd_input));
    if (strlen(input) > 0) {
        run_custom_shell_logic(input);
        gtk_entry_set_text(GTK_ENTRY(cmd_input), "");
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // 1. Main Window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Custom Linux Shell - Admin Suite");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 2. Main Vertical Box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // 3. Header Bar (System Monitor & Help)
    GtkWidget *header_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), header_hbox, FALSE, FALSE, 5);

    GtkWidget *sys_mon_btn = gtk_button_new_with_label("System Monitor (GUI)");
    GtkWidget *help_btn = gtk_button_new_with_label("Help");
    g_signal_connect(sys_mon_btn, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(help_btn, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    gtk_box_pack_start(GTK_BOX(header_hbox), sys_mon_btn, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(header_hbox), help_btn, FALSE, FALSE, 5);

    // 4. Middle Section (Terminal Area & Side Buttons)
    GtkWidget *middle_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), middle_hbox, TRUE, TRUE, 5);

    // Terminal Screen (Left)
    output_display = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_display), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(output_display), FALSE);
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), output_display);
    gtk_box_pack_start(GTK_BOX(middle_hbox), scrolled_window, TRUE, TRUE, 5);

    // Styling: Dark Terminal Look
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, "textview { color: #00FF00; background-color: #000000; font-family: Monospace; }", -1, NULL);
    gtk_style_context_add_provider(gtk_widget_get_style_context(output_display), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Side Buttons Panel (Right)
    GtkWidget *sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(middle_hbox), sidebar, FALSE, FALSE, 5);

    // Buttons List
    const char *side_btns[] = {"LS", "CLEAR", "HISTORY", "HELP", "MAN", "RM", "MKDIR", "ECHO", "EXPORT"};
    for (int i = 0; i < 9; i++) {
        GtkWidget *b = gtk_button_new_with_label(side_btns[i]);
        g_signal_connect(b, "clicked", G_CALLBACK(on_button_clicked), NULL);
        gtk_box_pack_start(GTK_BOX(sidebar), b, FALSE, FALSE, 2);
    }

    // 5. Footer (Input Field & Run Button)
    GtkWidget *footer_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), footer_hbox, FALSE, FALSE, 10);

    cmd_input = gtk_entry_new();
    g_signal_connect(cmd_input, "activate", G_CALLBACK(on_run_action), NULL); // Enter key par chalega
    gtk_box_pack_start(GTK_BOX(footer_hbox), cmd_input, TRUE, TRUE, 5);

    GtkWidget *run_btn = gtk_button_new_with_label("Run");
    g_signal_connect(run_btn, "clicked", G_CALLBACK(on_run_action), NULL);
    gtk_box_pack_start(GTK_BOX(footer_hbox), run_btn, FALSE, FALSE, 5);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
