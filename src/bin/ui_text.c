#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "ui_text.h"
#include "../lib/util.h"
#include "../lib/spp.h"
#include "../lib/define.h"
#include "man_tester.xxd"
#include "parser.h"

bool show_help;
char nconfig[256];
char *pconfig;
char *config;

int cargc = 0;
char **cargv = NULL;
struct sppArgs qargs;

static struct option long_options[] = {
    /* These options set a flag. */

    {"add", no_argument, 0, 'a'},
    {"rm", no_argument, 0, 'r'},
    {"show-links", no_argument, 0, 'l'},
    {"cat", no_argument, 0, 'c'},
    {"edit", no_argument, 0, 'e'},

    {"help", no_argument, &show_help, 'h'},

    /* These options don't set a flag.
       We distinguish them by their indices. */
    {"type", required_argument, 0, 't'},
    {"data", required_argument, 0, 'd'},
    {"log", required_argument, 0, 'L'},
    {"out", required_argument, 0, 'o'},
    {"config", required_argument, 0, 'C'},

    {"build", required_argument, 0, 'b'},

    {"topic", required_argument, 0, 'T'},
    {"id", required_argument, 0, 'i'},
    
    {"name", required_argument, 0, 'N'},
    {"index", required_argument, 0, 'I'},
    {"degree", required_argument, 0, 'D'},
    {"room", required_argument, 0, 'R'},
    {"topic-type", required_argument, 0, 'Y'},
    {"hours", required_argument, 0, 'H'},
    {"date", required_argument, 0, 'A'},
    {0, 0, 0, 0}
};


void
ui_show_description (FILE * f)
{
    /*
    fprintf (f, \
        "Program zarządzający bazą studentów, prowadzących i przedmiotów.");
    */
}


void
ui_show_options (FILE * f)
{
    int index = 0;
    fprintf (f, "options:\n");
    while (long_options[index].name) {
        fprintf (f, " -%c --%s;", long_options[index].val,
                 long_options[index].name);
        index++;
    }
    fprintf (f, "\n");
}

void
ui_show_help (FILE * f)
{
    fprintf (f, man_tester);
    /* ui_show_options(f); */
}

void
ui_init_arguments ()
{

    config=NULL;
    qargs.mode = 0;
    qargs.data = NULL;
    qargs.log = NULL;
    qargs.out = NULL;
    qargs.build =NULL;

    qargs.id = -1;

    qargs.name = NULL;
    qargs.degree = NULL;
    qargs.room = NULL;
    qargs.hours = -1;
    qargs.date = NULL;
    qargs.topic = NULL;
    qargs.topic_type = NULL;
    qargs.index = -1;
}

int
ui_setup_arguments (int argc, char **argv)
{
    int c;
    optind = 0;

    while (1) {

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv,
                         "argcevhfbyd:lo:C:x:X:p:n:P:T:i:m:M:S:B:Y:t:",
                         long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;
        switch (c) {
        case 0:
            /* If this option set a flag, do nothing else now. */
            /* if (long_options[option_index].flag != 0)
               break; */

            break;
        case 'a':
            qargs.mode = 1;
            break;
        case 'r':
            qargs.mode = 2;
            break;
        case 'l':
            qargs.mode = 3;
            break;
        case 'c':
            qargs.mode = 4;
            break;
        case 'e':
            qargs.mode = 5;
            break;
        case 'h':
            show_help = TRUE;
            break;
        case 'd':
            qargs.data = optarg;
            break;
        case 'L':
            qargs.log = optarg;
            break;
        case 'o':
            qargs.out = optarg;
            break;
        case 'C':
            config = optarg;
            break;
        case 'b':
            qargs.build = optarg;
            qargs.mode = 8;
            break;
        case 'T':
            qargs.topic = optarg;
            if (strlen (qargs.topic) > MAX_TOPIC)
                return 111;
            break;
        case 'i':
            if (isdigit(*optarg)) qargs.id=strtol(optarg, NULL, 10);
            else return 112;
            break;
        case 'N':
            qargs.name = optarg;
            if (strlen (qargs.name) > MAX_NAME)
                return 111;
            break;
        case 'I':
            if (isdigit(*optarg)) qargs.index=strtol(optarg, NULL, 10);
            else return 112;
            break;
        case 'D':
            qargs.degree = optarg;
            if (strlen (qargs.degree) > MAX_DEGREE)
                return 111;
            break;
        case 'R':
            qargs.room = optarg;
            if (strlen (qargs.room) > MAX_ROOM)
                return 111;
            break;
        case 't':
            qargs.type = optarg[0];
            break;
        case 'Y':
            qargs.topic_type = optarg;
            if (strlen (qargs.topic_type) > MAX_TOPIC_TYPE)
                return 111;
            break;
        case 'A':
            qargs.date = optarg;
            if (strlen (qargs.date) > MAX_DATE)
                return 111;
            break;
        case 'H':
            if (isdigit(*optarg)) qargs.hours=strtol(optarg, NULL, 10);
            else return 112;
            break;
        case '?':
            fprintf (stderr, "%s:%d ! E: Unknown argument..\n", __FILE__, __LINE__ );
            return 1;
            /* getopt_long already printed an error message. */
            break;

        default:
            abort ();
        }
    }
    if (show_help) {
        ui_show_help (stderr);
        return 1;
    }
    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        fprintf (stderr, "%s:%d ! E: non-option ARGV-elements: ", __FILE__, __LINE__ );
        while (optind < argc)
            fprintf (stderr, "%s:%d %s ", __FILE__, __LINE__ , argv[optind++]);
        fprintf (stderr, "%s:%d \n", __FILE__, __LINE__ );
        fprintf (stderr, "%s:%d ! E: Aborting..\n", __FILE__, __LINE__ );
        return 1;
    }

    return 0;
}

int loadConfig(char *path)

{
    int i;
    bool comment;
    long lSize;
    char *buffer;
    size_t result;
    FILE *pFile=NULL;

    pFile = fopen (path, "r");
    
    if(pFile) {
        fseek(pFile,0,SEEK_END);
        lSize = ftell(pFile);
        rewind(pFile);
        buffer = (char*) malloc(sizeof(char)*lSize);
        if(buffer==NULL) {
            fprintf(stderr,"Unable to allocate memory!\n");
            return EIO;
        }
        result = fread(buffer,1,lSize,pFile);
        if(result!=lSize) {
            fprintf(stderr,"Reading error!\n");
            return EIO;
        }
        fclose(pFile);
        comment=FALSE;
        for(i=0;i<lSize;i++) {
            if(buffer[i]=='#') {
                buffer[i]=' ';
                comment=TRUE;
            }
            else if(buffer[i]=='\n'){
                buffer[i]=' ';
                if(comment)
                    comment=FALSE;
            }
            else if(comment)
                buffer[i]=' ';
        }
      
        str2argv(buffer);
        cargc=getArgc();
        cargv=getArgv();
        cargv[0]=malloc(strlen("./config"));
        strcpy(cargv[0],"./config");

        free(buffer);
        return 0;

    }
    else
        return EIO;
}

int
ui_run (int argc, char **argv)
{
    int i = 0;
    int ret = EXIT_SUCCESS;
    int ret2 = 0;
    FILE *flog=NULL;

    ui_show_description (stderr);

    if (argc < 2) {
        ui_show_help (stderr);
        return EXIT_SUCCESS;
    }
    else {
        if(getenv("SPPRC"))
            pconfig = getenv("SPPRC");
        else {
            strcat (nconfig, getenv ("HOME"));
            strcat (nconfig, "/.spprc");
            pconfig = nconfig;
        }
        
        loadConfig(pconfig);
        


        ui_init_arguments ();
        if (cargv)
            if ((ret = ui_setup_arguments (cargc, cargv)))
                fprintf(stderr, "%s:%d ! W: corrupted config file %s. Ignoring!\n", __FILE__, __LINE__ ,pconfig);

        if ((ret = ui_setup_arguments (argc, argv))) {
            fprintf(stderr, "%s:%d ! E: while parsing parameters. Aborting!\n", __FILE__, __LINE__ );
            return ret;
        }

        if (config!=NULL)
        {
            loadConfig(config);

            if (cargv)
                if ((ret = ui_setup_arguments (cargc, cargv)))
                    fprintf(stderr, "%s:%d ! W: corrupted config file %s. Ignoring..\n", __FILE__, __LINE__ ,config);

            if ((ret = ui_setup_arguments (argc, argv))) {
                fprintf(stderr, "%s:%d ! E: while parsing parameters. Aborting!\n", __FILE__, __LINE__ );
                return ret;
            }
        }
    }

    if ((ret2 = spp_setup (&qargs))) {
        flog=spp_get_log();
        fprintf (flog,
                 "! E:  ERROR during initialization No. %d\n", ret2);
        ret = ret2;
    }
    else {
        flog=spp_get_log();
        if ((ret2 = spp_run ())) {
            fprintf (flog, "%s:%d ! E:  ERROR during running No. %d\n", __FILE__, __LINE__ ,
                     ret2);
            ret = ret2;
        }
    }

    spp_finish ();

    if (cargc) {
        for (i = 0; i <= cargc; i++)
            free (cargv[i]);
    }

    return ret;
}
