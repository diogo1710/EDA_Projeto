#include "main.h"

// code is concurrent so this is safe
static Job *first = NULL;
static unsigned int jobs = 0; // keep track the amount of jobs

void add_job(Job *head, Job *j) {
    if (!j) {
        return;
    }
    Job *iter = head;
    if (!head) {
        first = j;
    } else {
        while (iter->next != NULL) {
            iter = iter->next;
        }
        iter->next = j;
    }
}

void add_opr(Operation *head, Operation *o) {
    if (!o) {
        return;
    }
    if (!head) {
        head = o;
        return;
    }
    Operation *iter = head;
    while (iter->next) {
        iter = iter->next;
    }
    iter->next = o;
}

// Adiciona opcao
void add_opt(Option *head, Option *o) {
    if (!o) {
        return;
    }
    if (!head) {
        head = o;
        return;
    }
    Option *iter = head;
    while (iter->next) {
        iter = iter->next;
    }
    iter->next = o;
}

Job *new_job(unsigned int job_n, Operation *opr) {
    Job *j = malloc(sizeof(Job));
    if (!j) {
        exit(-1);
    }
    j->next = NULL;
    j->job_n = job_n;
    j->operations = opr;
    return j;
}

Operation *new_opr(unsigned int opr_n, Option *opt) {
    Operation *o = malloc(sizeof(Operation));
    if (!o) {
        exit(-1);
    }
    o->next = NULL;
    o->options = opt;
    o->opr_n = opr_n;
    return o;
}

// cria opcao nova
Option *new_opt(unsigned int m, unsigned int p, unsigned int opr_n) {
    Option *o = malloc(sizeof(Option));
    if (!o) {
        exit(-1);
    }
    o->next = NULL;
    o->opt_n = opr_n;
    o->machine = m;
    o->prc_time = p;
    return o;
}

void del_opt(Option *head, Option *o) {
    Option *iter = head;
    Option *prev = iter;
    while (iter != NULL) {
        if (iter == o) {
            prev->next = iter->next;
            if (iter == head)
                head = iter->next;
            free(iter);
            return;
        }
        prev = iter;
        iter = iter->next;
    }
}

void del_opr(Operation *head, Operation *o) {
    Operation *iter = head;
    Operation *prev = iter;
    while (iter != NULL) {
        if (iter == o) {
            prev->next = iter->next;
            if (iter == head)
                head = iter->next;
            free(iter);
            return;
        }
        prev = iter;
        iter = iter->next;
    }
}

void menu_adiciona_opcao() {
    unsigned int job_n;
    unsigned int opr_n;
    unsigned int pos;
    unsigned int machine;
    unsigned int prc_time;

    printf("insira o numero de Trabalho: ");
    if (scanf("%u", &job_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    printf("insira o numero de operacao: ");
    if (scanf("%u", &opr_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    Job *iter = first;
    while (iter) {
        Operation *opr_iter = iter->operations;
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            if (iter->job_n == job_n && opr_iter->opr_n == opr_n) {
                printf("Insira o numero da maquina: ");
                if (scanf("%u", &machine) != 1) {
                    clean_stdin();
                    puts("valores nao reconhecidos");
                    return;
                }
                printf("Insira o tempo de processamento: ");
                if (scanf("%u", &prc_time) != 1) {
                    clean_stdin();
                    puts("valores nao reconhecidos");
                    return;
                }
                Option *o = new_opt(machine, prc_time, opr_iter->opts + 1);
                add_opt(opr_iter->options, o);
                opr_iter->opts++;
                clean_stdin();
                return;
            }
            opr_iter = opr_iter->next;
        }
        iter = iter->next;
    }
    puts("valores nao reconhecidos");
    return;
}

void menu_remove_opcao() {
    unsigned int job_n;
    unsigned int opr_n;
    unsigned int opt_n;

    printf("insira o numero de Trabalho: ");
    if (scanf("%u", &job_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    printf("insira o numero de operacao: ");
    if (scanf("%u", &opr_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    printf("insira o numero de opcao: ");
    if (scanf("%u", &opt_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    Job *j_iter = first;
    while (j_iter) {
        Operation *opr_iter = j_iter->operations;
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            while (opt_iter) {
                if (j_iter->job_n == job_n && opr_iter->opr_n == opr_n &&
                    opt_iter->opt_n == opt_n) {
                    Option *opt_iter2 = opt_iter->next;
                    if (opr_iter->options == opt_iter) {
                        // head changed
                        opr_iter->options = opt_iter->next;
                    }
                    del_opt(opr_iter->options, opt_iter);
                    // cicle the list and remove 1 to element number
                    while (opt_iter2) {
                        opt_iter2->opt_n--;
                        opt_iter2 = opt_iter2->next;
                    }
                    clean_stdin();
                    return;
                }
                opt_iter = opt_iter->next;
            }
            opr_iter = opr_iter->next;
        }
        j_iter = j_iter->next;
    }
}

void menu_altera_opcao() {
    unsigned int job_n;
    unsigned int opr_n;
    unsigned int opt_n;
    unsigned int machine;
    unsigned int prc_time;

    printf("insira o numero de Trabalho: ");
    if (scanf("%u", &job_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    printf("insira o numero de operacao: ");
    if (scanf("%u", &opr_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    printf("insira o numero de opcao: ");
    if (scanf("%u", &opt_n) != 1) {
        clean_stdin();
        puts("valores nao reconhecidos");
        return;
    }
    Job *j_iter = first;
    while (j_iter) {
        Operation *opr_iter = j_iter->operations;
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            Option *last = NULL;
            while (opt_iter) {
                if (j_iter->job_n == job_n && opr_iter->opr_n == opr_n &&
                    opt_iter->opt_n == opt_n) {
                    printf("Insira o numero da maquina: ");
                    if (scanf("%u", &machine) != 1) {
                        clean_stdin();
                        puts("valores nao reconhecidos");
                        return;
                    }
                    printf("Insira o tempo de processamento: ");
                    if (scanf("%u", &prc_time) != 1) {
                        clean_stdin();
                        puts("valores nao reconhecidos");
                        return;
                    }
                    Option *o = malloc(sizeof(Option));
                    o->prc_time = prc_time;
                    o->machine = machine;
                    o->opt_n = opt_n;
                    if (last) {
                        last->next = o;
                    }
                    if (opr_iter->options == opt_iter) {
                        // head changed
                        opr_iter->options = o;
                    }
                    o->next = opt_iter->next;
                    free(opt_iter);
                    clean_stdin();
                    return;
                }
                last = opt_iter;
                opt_iter = opt_iter->next;
            }
            opr_iter = opr_iter->next;
        }
        j_iter = j_iter->next;
    }
}

void print_list() {
    Job *j_iter = first;
    while (j_iter) {
        Operation *opr_iter = j_iter->operations;
        printf("\njob %u->", j_iter->job_n);
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            printf(" %u: ", opr_iter->opts);
            while (opt_iter) {
                printf("%u", opt_iter->opt_n);
                printf("(%u,", opt_iter->machine);
                printf("%u) ", opt_iter->prc_time);
                opt_iter = opt_iter->next;
            }
            opr_iter = opr_iter->next;
        }
        j_iter = j_iter->next;
    }
}

void melhor_caminho() {
    Job *j_iter = first;
    while (j_iter) {
        unsigned int total = 0;
        Operation *opr_iter = j_iter->operations;
        printf("\njob %d-> ", j_iter->job_n);
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            Option *min = opt_iter;
            while (opt_iter) {
                if (opt_iter->prc_time < min->prc_time) {
                    min = opt_iter;
                }
                opt_iter = opt_iter->next;
            }
            printf("%d", min->opt_n);
            printf("(%d,", min->machine);
            printf("%d) ", min->prc_time);
            total += min->prc_time;
            opr_iter = opr_iter->next;
        }
        printf(" - total %d", total);
        j_iter = j_iter->next;
    }
}

void pior_caminho() {
    Job *j_iter = first;
    while (j_iter) {
        unsigned int total = 0;
        Operation *opr_iter = j_iter->operations;
        printf("\njob %d-> ", j_iter->job_n);
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            Option *max = opt_iter;
            while (opt_iter) {
                if (opt_iter->prc_time > max->prc_time) {
                    max = opt_iter;
                }
                opt_iter = opt_iter->next;
            }
            printf("%d", max->opt_n);
            printf("(%d,", max->machine);
            printf("%d) ", max->prc_time);
            total += max->prc_time;
            opr_iter = opr_iter->next;
        }
        printf(" - total %d", total);
        j_iter = j_iter->next;
    }
}

void tempo_medio() {
    Job *j_iter = first;
    size_t total = 0;
    float opt_total = 0;
    while (j_iter) {
        Operation *opr_iter = j_iter->operations;
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            while (opt_iter) {
                opt_total++;
                total += opt_iter->prc_time;
                opt_iter = opt_iter->next;
            }
            opr_iter = opr_iter->next;
        }
        j_iter = j_iter->next;
    }
    printf("%f\n", opt_total);
    printf("%lu\n", total);
    printf("%f", total / opt_total);
}

void write() {
    FILE *fp;
    if ((fp = fopen("./tp_new.fjs", "w+")) == NULL) {
        exit(-1);
    }
    Job *j_iter = first;
    while (j_iter) {
        Operation *opr_iter = j_iter->operations;
        fprintf(fp, "%u ", j_iter->oprs - 1);
        while (opr_iter) {
            Option *opt_iter = opr_iter->options;
            fprintf(fp, "%u ", opr_iter->opts);
            while (opt_iter) {
                fprintf(fp, "%u ", opt_iter->machine);
                fprintf(fp, "%u ", opt_iter->prc_time);
                opt_iter = opt_iter->next;
            }
            opr_iter = opr_iter->next;
        }
        fprintf(fp, "\n");
        j_iter = j_iter->next;
    }
}

void show_menu() {
    puts("Prima um caracter:");
    puts("  a - adicionar");
    puts("  r - remover");
    puts("  x - alterar");
    puts("  m - caminho mais lento");
    puts("  M - caminho mais rapido");
    puts("  j - media");
    puts("  l - listar a lista");
    puts("  e - sair");
    puts("  s - salvar em ficheiro");
}

void switch_menu() {
    printf("\n    -> ");
    char input;
    if ((input = getchar()) != 1) {
        clean_stdin();
    }
    switch (input) {
        case 'a': // adicao
            menu_adiciona_opcao();
            break;
        case 'r': // remocao
            menu_remove_opcao();
            break;
        case 'x': // alterar
            menu_altera_opcao();
            break;
        case 'c': // clear
            system("cls");
            show_menu();
            break;
        case 'm': // menor caminho
            melhor_caminho();
            break;
        case 'M': // maior caminho
            pior_caminho();
            break;
        case 'j': // media
            tempo_medio();
            break;
        case 'e': // exit
            return;
        case 'l': // imprimir a lista
            print_list();
            break;
        case 's': // dar save em um ficheiro
            write();
            break;
        default:
            puts("Caracter nao reconhecido.");
            break;
    }
    puts("");
    switch_menu();
}

void menu() {
    show_menu();
    switch_menu();
}

void parse_input() {
    FILE *fp;
    if ((fp = fopen("./tabela.txt", "r")) == NULL) {
        exit(-1);
    }
    char *line = NULL; // linha lida do ficheiro
    size_t len;
    ssize_t read;
    // numero da linha -> numero do trabalho
    int job_n = 1;
    // numero de operacoes para o trabalho
    int opr_n = 1;
    Job *job_ptr = NULL;
    while ((read = getline(&line, &len, fp)) != -1) {
        // devolve uma string com a informacao da linha
        // quando devolver -1, acabou o ficheiro.
        // procurar o primeiro espaco e devolve a string ate " ".
        char *delims = strtok(line, " ");
        int opr_max = atoi(delims);
        Operation *opr_head = NULL;

        delims = strtok(NULL, " ");
        while (delims != NULL) {
            int opcoes = atoi(delims);
            delims = strtok(NULL, " ");
            Option *opt_head = NULL;

            for (int i = 0; i < opcoes; i++) {
                Option *opt;
                unsigned int machine = atoi(delims);
                delims = strtok(NULL, " ");
                unsigned int processing_time = atoi(delims);
                delims = strtok(NULL, " ");

                opt = new_opt(machine, processing_time, i + 1);
                add_opt(opt_head, opt);
                // control head pointer
                if (i == 0) {
                    opt_head = opt;
                }
            }
            Operation *opr = new_opr(opr_n, opt_head);
            add_opr(opr_head, opr);
            if (opr_head == NULL) {
                opr_head = opr;
            }
            opr->opts = opcoes;
            opr_n++;
        }
        job_ptr = new_job(job_n, opr_head);
        add_job(first, job_ptr);
        job_ptr->oprs = opr_n;
        job_n++;
        opr_n = 1;
    }
    fclose(fp);
    if (line) {
        free(line);
    };
}

void ext(int status) {
    if (first) {
        free(first);
    }
    exit(status);
}

int main() {
    parse_input();
    menu();
    ext(0);
}

// Utilitarios
ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

// fflush(stdin) is bad practice
void clean_stdin() {
    for (int c; (c = getchar()) != '\n' && c != EOF;)
        ;
}