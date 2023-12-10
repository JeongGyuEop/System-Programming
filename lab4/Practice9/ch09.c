#include <gtk/gtk.h>
#include <math.h>

// 계산기의 상태를 나타내는 열거형
typedef enum {
    STATE_NONE,
    STATE_ADDITION,
    STATE_SUBTRACTION,
    STATE_MULTIPLICATION,
    STATE_DIVISION
} CalculatorState;

GtkWidget *entry;               // 텍스트 입력 필드
CalculatorState current_state;  // 현재 계산기 상태
double current_value;           // 현재 입력된 값

// 숫자 버튼 클릭 시 호출되는 콜백 함수
void on_number_button_clicked(GtkButton *button, gpointer user_data) {
    const gchar *text = gtk_button_get_label(button);
    gchar *current_text = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));

    // 현재 입력된 값에 선택한 숫자를 추가
    gchar *new_text = g_strconcat(current_text, text, NULL);
    gtk_entry_set_text(GTK_ENTRY(entry), new_text);

    g_free(current_text);
    g_free(new_text);
}

// 연산자 버튼 클릭 시 호출되는 콜백 함수
void on_operator_button_clicked(GtkButton *button, gpointer user_data) {
    const gchar *text = gtk_button_get_label(button);
    gchar *current_text = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));

    // 현재 입력된 값과 상태 저장
    current_value = atof(current_text);
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    
    if (g_strcmp0(text, "+") == 0) {
        current_state = STATE_ADDITION;
    } else if (g_strcmp0(text, "-") == 0) {
        current_state = STATE_SUBTRACTION;
    } else if (g_strcmp0(text, "*") == 0) {
        current_state = STATE_MULTIPLICATION;
    } else if (g_strcmp0(text, "/") == 0) {
        current_state = STATE_DIVISION;
    }

    g_free(current_text);
}

// 등호 버튼 클릭 시 호출되는 콜백 함수
void on_equal_button_clicked(GtkButton *button, gpointer user_data) {
    gchar *current_text = g_strdup(gtk_entry_get_text(GTK_ENTRY(entry)));
    double new_value = atof(current_text);
    g_free(current_text);

    // 현재 상태에 따라 연산 수행
    switch (current_state) {
        case STATE_ADDITION:
            new_value = current_value + new_value;
            break;
        case STATE_SUBTRACTION:
            new_value = current_value - new_value;
            break;
        case STATE_MULTIPLICATION:
            new_value = current_value * new_value;
            break;
        case STATE_DIVISION:
            if (new_value != 0) {
                new_value = current_value / new_value;
            } else {
                // 0으로 나누는 경우 오류 처리
                GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Cannot divide by zero!");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                return;
            }
            break;
        default:
            // 상태가 정의되지 않은 경우 현재 값 유지
            new_value = current_value;
            break;
    }

    // 결과를 텍스트 입력 필드에 표시
    gchar *result_text = g_strdup_printf("%g", new_value);
    gtk_entry_set_text(GTK_ENTRY(entry), result_text);
    g_free(result_text);
}

// 초기화 버튼 클릭 시 호출되는 콜백 함수
void on_clear_button_clicked(GtkButton *button, gpointer user_data) {
    // 텍스트 입력 필드 초기화
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    current_value = 0.0;
    current_state = STATE_NONE;
}

// 메인 함수
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // 창 생성
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "간단한 계산기");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 그리드 생성
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // 텍스트 입력 필드 생성
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1);
    gtk_entry_set_tabs(GTK_ENTRY(entry), FALSE);

    // 숫자 및 연산자 버튼 생성 및 연결
    const gchar *button_labels[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };

    for (int i = 0; i < 16; ++i) {
        GtkWidget *button = gtk_button_new_with_label(button_labels[i]);
        gtk_widget_set_hexpand(button, TRUE);
        gtk_widget_set_vexpand(button, TRUE);

        if (i == 14) {
            // "=" 버튼의 경우 따로 처리
            g_signal_connect(button, "clicked", G_CALLBACK(on_equal_button_clicked), NULL);
        } else if (i % 4 == 3 && i != 11) {
            // 연산자 버튼의 경우 따로 처리
            g_signal_connect(button, "clicked", G_CALLBACK(on_operator_button_clicked), NULL);
        } else if (i == 11) {
            // "C" 버튼의 경우 따로 처리
            GtkWidget *clear_button = gtk_button_new_with_label("C");
            g_signal_connect(clear_button, "clicked", G_CALLBACK(on_clear_button_clicked), NULL);
            gtk_grid_attach(GTK_GRID(grid), clear_button, i % 4, i / 4 + 1, 1, 1);
        } else {
            // 숫자 버튼의 경우 따로 처리
            g_signal_connect(button, "clicked", G_CALLBACK(on_number_button_clicked), NULL);
        }

        if (i != 11) {
            int row = i / 4 + 1;
            int col = i % 4;
            gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
        }
    }

    // 창 표시
    gtk_widget_show_all(window);

    // 이벤트 루프 시작
    gtk_main();

    return 0;
}
