
#include "newgrep.h"

int find_file(int argc, char** argv) {
    
    int index = 0;
    FILE* fp = NULL;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
             fp = fopen(argv[i], "rb");
             if (fp != NULL) {
                // находим файлы в аргументах и от них запускаем работу 

             }
        }
    }
}

int main(int argc, char** argv) {
    int opt;
    int reg_flag = 0;
    int targetStringIndecies[10]; // поиск флагов и их значений нужно перевести в отдельную функцию после поиска файлов
    static struct option const long_options[] =  
    {
      {"count", no_argument, NULL, 'c'},
      {"file", required_argument, NULL, 'f'},
      {"files-with-matches", no_argument, NULL, 'l'},
      {"ignore-case", no_argument, NULL, 'i'},
      {"line-number", no_argument, NULL, 'n'},
      {"no-filename", no_argument, NULL, 'h'},
      {"no-messages", no_argument, NULL, 's'},
      {"only-matching", no_argument, NULL, 'o'},
      {"regexp", required_argument, NULL, 'e'},
      {"invert-match", no_argument, NULL, 'v'},
      {0, 0, 0, 0}
    };
    HashTable* flags = create_table(CAPACITY);
    const int bufferSize = 4096;
    int counter_lines = 0;
    char** patterns = NULL; // список шаблонов, которые будем искать в тексте
    switch (opt) { 
            case 'e':
                ht_insert(flags, "e", 0); // если будет ещё 1 флаг - автоматически сдвинется 
                patterns = (char**)realloc(patterns, sizeof(patterns) + sizeof(char**)); // перевыделяем память для хранения еще одной ссылки на шаблон
                patterns[ht_search(flags, "e")] = (char*)malloc(strlen(optarg) * sizeof(char)); // выделяем память для шаблона
                strcpy(patterns[ht_search(flags, "e")], optarg); // копируем шаблон в выделенную память
                break;
            case '?':
                printf("usage: grep [option] [-eivclnhsfo] [file ...]\n");
                exit(1);
            default:
                ht_insert(flags, opt +"", 1);
    }
    find_file(argc, argv);
    for (int i = 0; i < ht_search(flags, "e"); ++i) {
        free(patterns[i]);
    }
    free(patterns);
    return 0;
}
