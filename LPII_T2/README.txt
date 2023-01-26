Aluno: Johannes Cavalcante [11400981]

Trabalho Prático: Mini Servidor HTTP, com Threads e Monitor.

Dividi o programa em alguns arquivos, por questões de organização. Temos então 'main.cpp' (o código principal), 'LogMonitor.cpp' e 'LogMonitor.h' implementam a classe Monitor para manipulação do Log e 'Request.cpp' e 'Request.h' implementam uma classe Request, que julguei necessária por motivos de organização.

Escrevi um arquivo Makefile para tornar a compilação mais prática, assim, para compilar o programa basta executar o comando '$ make all' no diretório raiz do programa (onde 'main.cpp' está). Há outra opção para o Makefile: é possível usar o camando '$ make clean'. Isso vai apagar o executável, o arquivo de log gerado pelo programa e qualquer arquivo temporário que surgir.

Uma vez compilado, pode-se executar o programa com o comando '$ ./lp2-t2'.

Assim como estabelecido para o trabalho, existe uma pasta files, a qual contém os possíveis aruivos que podem ser requisitados ao server.

