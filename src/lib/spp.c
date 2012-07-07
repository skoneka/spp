#include    "spp.h"

struct sppArgs *qa = NULL;

FILE *fdata = NULL;
FILE *flog = NULL;
FILE *fout = NULL;

int i, j;
FILE *ftmp = NULL;
bool overflow = FALSE;
st_rekord_student records_students[MAX_RECORDS];
st_rekord_topic records_topics[MAX_RECORDS];
st_rekord_lecturer records_lecturers[MAX_RECORDS];

int records_n = MAX_RECORDS;

st_rekord_student record_student;
st_rekord_topic record_topic;
st_rekord_lecturer record_lecturer;

/* Errors:
 *
 * -1 - bad/insufficient arguments
 *  1 - did not receive sppArgs structure
 *  2 - required filename is unknown
 *  3 - unable to open database file
 *
 */

int mode_cat ();
int mode_rm ();
int mode_edit ();
int mode_show_links();
int mode_build ();

int create_file(char *fname);
char *get_db_filename(char *prefix, char *extension);

void set_record_student_and_fill (st_rekord_student * record, char *name,
        int index,char *topic);
void set_record_lecturer_and_fill (st_rekord_lecturer * record, char *name,
        char *degree, char *room,char *topic);
void set_record_topic_and_fill (st_rekord_topic * record, char *name,
        char *topic_type, int hours,char *date);
char *
get_db_filename(char *prefix, char *extension)
{
    int data_len = strlen(prefix);
    int ext_len = strlen(extension);
    char *fname = malloc((data_len+ext_len+1)*sizeof(char));
    strcpy(fname, prefix);
    strcat(fname,extension);
    return fname;
}

FILE *
spp_get_log() 
{
    if(flog)
        return flog;
    else
        return stderr;
}
int
spp_setup (struct sppArgs *qargs)
{
    srand ((int) time (NULL));

    if (qargs == NULL)
        return 1;
    else
        qa = qargs;

    if (qargs->log == NULL)
        flog = stderr;
    else {
        if (!(flog = fopen (qargs->log, "w"))) {
            fprintf(flog , "%s:%d ! E: Unable to create\"%s\"\n", __FILE__, __LINE__ ,qargs->log);
            return 4;
        }
    }

    if (qargs->out == NULL)
        fout = stdout;
    else {
        if (!(fout = fopen (qargs->out, "w"))){
            fprintf(flog , "%s:%d ! E: Unable to create \"%s\"\n", __FILE__, __LINE__ ,qargs->out);
            return 5;
        }
    }

    return 0;
}

void
spp_finish ()
{

    (flog == stderr || flog == NULL) ? 0 : fclose (flog);
    (fout == stdout || fout == NULL) ? 0 : fclose (fout);
}

void
set_record_student_and_fill (st_rekord_student * record, char *name,
        int index,char *topic)
{

    (name) ? strncpy (record->name, name,
                        strlen (name) + 1) : strcpy (record->name, " ");
    record->index = index;
    (topic) ? strncpy (record->topic, topic,
                         strlen (topic) + 1) : strcpy (record->topic,
                                                         " ");
}
void
set_record_lecturer_and_fill (st_rekord_lecturer * record, char *name,
        char *degree, char *room,char *topic)
{

    (name) ? strncpy (record->name, name,
                        strlen (name) + 1) : strcpy (record->name, " ");
    (degree) ? strncpy (record->degree, degree,
                        strlen (degree) + 1) : strcpy (record->degree, " ");
    (room) ? strncpy (record->room, room,
                        strlen (room) + 1) : strcpy (record->room, " ");
    (topic) ? strncpy (record->topic, topic,
                         strlen (topic) + 1) : strcpy (record->topic,
                                                         " ");
}

void
set_record_topic_and_fill (st_rekord_topic * record, char *name,
        char *topic_type, int hours,char *date)
{

    (name) ? strncpy (record->name, name,
                        strlen (name) + 1) : strcpy (record->name, " ");
    (topic_type) ? strncpy (record->topic_type, topic_type,
                        strlen (topic_type) + 1) : strcpy (record->topic_type, " ");

    record->hours = hours;

    (date) ? strncpy (record->date, date,
                         strlen (date) + 1) : strcpy (record->date,
                                                         " ");
}

int
mode_add ()
{
    if(qa->type == 's') { /* student */
        char *fname = get_db_filename(qa->data, STUD_EXT);

        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        record_student.id = dbGetNewID(fdata);
        fclose (fdata); fdata= NULL;
        if (!(fdata = fopen (fname, "a"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        set_record_student_and_fill (&record_student, qa->name, qa->index,qa->topic);
        
        db_write_records_students (fdata, &record_student, 1);
        fclose (fdata);
        fdata= NULL;
        return 0;
    }
    else if(qa->type == 'l') { /* lecturer */
        char *fname = get_db_filename(qa->data, LECTURER_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        record_lecturer.id = dbGetNewID(fdata);
        fclose (fdata); fdata= NULL;
        if (!(fdata = fopen (fname, "a"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        set_record_lecturer_and_fill (&record_lecturer, qa->name, qa->degree , qa->room, qa->topic);
        db_write_records_lecturers (fdata, &record_lecturer, 1);
        fclose (fdata);
        fdata= NULL;
        return 0;
    }
    else if(qa->type == 't') { /* topic */
        char *fname = get_db_filename(qa->data, TOPIC_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        record_topic.id = dbGetNewID(fdata);
        fclose (fdata); fdata= NULL;
        if (!(fdata = fopen (fname, "a"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        set_record_topic_and_fill (&record_topic, qa->name, qa->topic_type, qa->hours, qa->date);
        db_write_records_topics (fdata, &record_topic, 1);
        fclose (fdata);
        fdata= NULL;
        return 0;
    }
    return 1;
}

int
mode_rm ()
{
    char *fname = NULL;
    if(qa->type == 's') {
        fname = get_db_filename(qa->data, STUD_EXT);
    }
    else if(qa->type == 'l') {
        fname = get_db_filename(qa->data, LECTURER_EXT);
    }
    else if(qa->type == 't') {
        fname = get_db_filename(qa->data, TOPIC_EXT);
    }
    else {
        fprintf(flog , "%s:%d ! E: Unknown entry type \"%c\"\n", __FILE__, __LINE__ ,qa->type);
        return 1;
    }
    if (!(fdata = fopen (fname, "r"))){
        fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
        return 3;
    }
    ftmp = tmpfile ();
    dbRemoveID(fdata,ftmp, qa->id);
    fclose(fdata); fdata=NULL;
    rewind (ftmp);
    if (!(fdata = fopen (fname, "w"))){
        fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
        return 3;
    }
    util_copy_file (ftmp, fdata);
    fclose(ftmp); ftmp=NULL;
    fclose(fdata); fdata=NULL;
    if (qa->type == 't') {
        fname = get_db_filename(qa->data, STUD_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        ftmp = tmpfile ();
        db_remove_topic_id_from_stud(fdata,ftmp, qa->id);
        fclose(fdata); fdata=NULL;
        rewind (ftmp);
        if (!(fdata = fopen (fname, "w"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        util_copy_file (ftmp, fdata);
        fclose(ftmp); ftmp=NULL;
        fclose(fdata); fdata=NULL;

        fname = get_db_filename(qa->data, LECTURER_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        ftmp = tmpfile ();
        db_remove_topic_id_from_lecturer(fdata,ftmp, qa->id);
        fclose(fdata); fdata=NULL;
        rewind (ftmp);
        if (!(fdata = fopen (fname, "w"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        util_copy_file (ftmp, fdata);
        fclose(ftmp); ftmp=NULL;
        fclose(fdata); fdata=NULL;
    }

    return 0;
}

int
mode_cat ()
{
    if(qa->type == 's') { /* student */
        int records_n=0;
        char *fname = get_db_filename(qa->data, STUD_EXT);
        fname = get_db_filename(qa->data, STUD_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }

        do {
            records_n = db_read_records_students (fdata, records_students, MAX_RECORDS, &overflow);
            int i;
            if (qa->id == -1)
                db_write_records_students (fout, records_students, records_n);
            else
                for (i=0; i<records_n; i++)
                    if (qa->id == records_students[i].id)
                        db_write_records_students (fout, &records_students[i], 1);
        } while (overflow);

        fclose (fdata);
        fdata= NULL;
    }
    else if(qa->type == 't') { /* topic */
        int records_n=0;
        char *fname = get_db_filename(qa->data, TOPIC_EXT);
        fname = get_db_filename(qa->data, TOPIC_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }

        do {
            records_n = db_read_records_topics (fdata, records_topics, MAX_RECORDS, &overflow);
            if (qa->id == -1)
                db_write_records_topics (fout, records_topics, records_n);
            else
                for (i=0; i<records_n; i++)
                    if (qa->id == records_topics[i].id)
                        db_write_records_topics (fout, &records_topics[i], 1);
        } while (overflow);

        fclose (fdata);
        fdata= NULL;
    }
    else if(qa->type == 'l') { /* lecturer */
        int records_n=0;
        char *fname = get_db_filename(qa->data, LECTURER_EXT);
        fname = get_db_filename(qa->data, LECTURER_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }

        do {
            records_n = db_read_records_lecturers (fdata, records_lecturers, MAX_RECORDS, &overflow);
            if (qa->id == -1)
                db_write_records_lecturers (fout, records_lecturers, records_n);
            else
                for (i=0; i<records_n; i++)
                    if (qa->id == records_lecturers[i].id)
                        db_write_records_lecturers (fout, &records_lecturers[i], 1);
        } while (overflow);

        fclose (fdata);
        fdata= NULL;
    }
    return 0;
}

int
mode_edit ()
{

    char *fname=NULL;
    if(qa->type == 's') {
        fname = get_db_filename(qa->data, STUD_EXT);
    }
    else if(qa->type == 'l') {
        fname = get_db_filename(qa->data, LECTURER_EXT);
    }
    else if(qa->type == 't') {
        fname = get_db_filename(qa->data, TOPIC_EXT);
    }
    else {
        fprintf(flog , "%s:%d ! E: Unknown entry type \"%c\"\n", __FILE__, __LINE__ ,qa->type);
        return 1;
    }
    if (!(fdata = fopen (fname, "r"))){
        fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
        return 3;
    }
    ftmp = tmpfile ();
    if(qa->type == 's') {
        do {
            records_n = db_read_records_students (fdata, records_students, MAX_RECORDS, &overflow);
            int i;
            for (i=0; i<records_n; i++) {
                if ( qa->id == records_students[i].id) {
                    if (qa->name)
                        strncpy(records_students[i].name, qa->name, MAX_NAME);
                    if (qa->index != -1)
                        records_students[i].index = qa->index;
                    if (qa->topic)
                        strncpy(records_students[i].topic, qa->topic, MAX_TOPIC);
                }
            }
            db_write_records_students (ftmp, records_students, records_n);
        } while (overflow);
    }
    else if(qa->type == 'l') {
        do {
            records_n = db_read_records_lecturers (fdata, records_lecturers, MAX_RECORDS, &overflow);
            int i;
            for (i=0; i<records_n; i++) {
                if ( qa->id == records_lecturers[i].id) {
                    if (qa->name)
                        strncpy(records_lecturers[i].name, qa->name, MAX_NAME);
                    if (qa->degree)
                        strncpy(records_lecturers[i].degree, qa->degree, MAX_DEGREE);
                    if (qa->room)
                        strncpy(records_lecturers[i].room, qa->room, MAX_ROOM);
                    if (qa->topic)
                        strncpy(records_lecturers[i].topic, qa->topic, MAX_TOPIC);
                }
            }
            db_write_records_lecturers (ftmp, records_lecturers, records_n);
        } while (overflow);
    }
    else if(qa->type == 't') {
        do {
            records_n = db_read_records_topics (fdata, records_topics, MAX_RECORDS, &overflow);
            int i;
            for (i=0; i<records_n; i++) {
                if ( qa->id == records_topics[i].id) {
                    if (qa->name)
                        strncpy(records_topics[i].name, qa->name, MAX_NAME);
                    if (qa->topic_type)
                        strncpy(records_topics[i].topic_type, qa->topic_type, MAX_TOPIC_TYPE);
                    if (qa->hours != -1)
                        records_topics[i].hours = qa->hours;
                    if (qa->date)
                        strncpy(records_topics[i].date, qa->date, MAX_DATE);
                }
            }
            db_write_records_topics (ftmp, records_topics, records_n);
        } while (overflow);
    }

    fclose(fdata); fdata=NULL;
    rewind (ftmp);
    if (!(fdata = fopen (fname, "w"))){
        fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
        return 3;
    }
    util_copy_file (ftmp, fdata);
    fclose(ftmp); ftmp=NULL;
    fclose(fdata); fdata=NULL;

    return 0;
}


int
mode_show_links()
{
    int links_arr[MAX_LINKS];
    int links_arr_i=0;
    char *fname = NULL;
    char *s=NULL;
    memset(links_arr, 0, MAX_LINKS);
    char topic_tmp[MAX_TOPIC];
    if(qa->type == 's') {
        fname = get_db_filename(qa->data, STUD_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        do {
            records_n = db_read_records_students (fdata, records_students, MAX_RECORDS, &overflow);
            int i;
            for (i=0; i<records_n; i++) {
                strncpy(topic_tmp, records_students[i].topic, MAX_TOPIC);
                if (qa->id == -1 || qa->id == records_students[i].id) {
                    s = strtok(topic_tmp, ",");
                    while (1) {
                        if (!s || links_arr_i >= MAX_LINKS)
                            break;
                        int sub_id = atoi(s);
                        if (sub_id) {
                            int j, found = FALSE;
                            for ( j=0; j<links_arr_i; j++) {
                                if (links_arr[j] == sub_id) {
                                    found = TRUE;
                                    printf("wtf %d", sub_id);
                                    break;
                                }
                            }
                            if (!found) {
                                links_arr[links_arr_i++] = sub_id;
                            }
                        }
                        s = strtok(NULL, ",");
                    }
                }
            }
        } while (overflow);
    }
    else if(qa->type == 'l') {
        fname = get_db_filename(qa->data, LECTURER_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        do {
            records_n = db_read_records_lecturers (fdata, records_lecturers, MAX_RECORDS, &overflow);
            int i;
            for (i=0; i<records_n; i++) {
                if (qa->id == -1 || qa->id == records_lecturers[i].id) {
                    strncpy(topic_tmp, records_lecturers[i].topic, MAX_TOPIC);
                    s = strtok(topic_tmp, ",");
                    while (1) {
                        if (!s || links_arr_i >= MAX_LINKS)
                            break;
                        int sub_id = atoi(s);
                        if (sub_id) {
                            int j, found = FALSE;
                            for ( j=0; j<links_arr_i; j++) {
                                if (links_arr[j] == sub_id) {
                                    found = TRUE;
                                    break;
                                }
                            }
                            if (!found)
                                links_arr[links_arr_i++] = sub_id;
                        }
                        s = strtok(NULL, ",");
                    }
                }
            }
        } while (overflow);
    }
    else if(qa->type == 't') {
        char *s = NULL;
        fname = get_db_filename(qa->data, LECTURER_EXT);
        fprintf(fout, "lecturers:\n");
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        do {
            records_n = db_read_records_lecturers (fdata, records_lecturers,
                    MAX_RECORDS, &overflow);
            int i;
            for (i=0; i<records_n; i++) {
                strncpy(topic_tmp, records_lecturers[i].topic, MAX_TOPIC);
                s = strtok(topic_tmp, ",");
                while(s){
                    int sub_id = atoi(s);
                    if (qa->id == sub_id) {
                        db_write_records_lecturers (fout, &records_lecturers[i],
                                1);
                    }
                    s = strtok(NULL, ",");
                }
            }
        } while (overflow);
        fname = get_db_filename(qa->data, STUD_EXT);
        fprintf(fout, "students:\n");
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        do {
            records_n = db_read_records_students (fdata, records_students,
                    MAX_RECORDS, &overflow);
            int i;
            for (i=0; i<records_n; i++) {
                strncpy(topic_tmp, records_students[i].topic, MAX_TOPIC);
                s = strtok(topic_tmp, ",");
                while(s){
                    int sub_id = atoi(s);
                    if (qa->id == sub_id) {
                        db_write_records_students (fout, &records_students[i],
                                1);
                    }
                    s = strtok(NULL, ",");
                }
            }
        } while (overflow);
    }
    else {
        fprintf(flog , "%s:%d ! E: Unknown entry type \"%c\"\n", __FILE__, __LINE__ ,qa->type);
        return 1;
    }
    fclose(fdata); fdata=NULL;

    if (qa->type == 's' || qa->type == 'l') {
        fname = get_db_filename(qa->data, TOPIC_EXT);
        if (!(fdata = fopen (fname, "r"))){
            fprintf(flog , "%s:%d ! E: Unable to open\"%s\"\n", __FILE__, __LINE__ , fname);
            return 3;
        }
        do {
            records_n = db_read_records_topics (fdata, records_topics, MAX_RECORDS, &overflow);
            int i,j;
            for (i=0; i<records_n; i++) {
                int sub_id = records_topics[i].id;
                for (j=0; j<links_arr_i; j++) {
                    if (sub_id == links_arr[j]) {
                        db_write_records_topics (stdout, &records_topics[i], 1);
                    }
                }
            }
        } while (overflow);
    }

    return 0;
}

int
create_file(char *fname)
{
    FILE *f = fopen(fname,"w") ;
    if(!f) {
        fprintf(flog , "%s:%d ! E: Unable to create \"%s\"\n", __FILE__, __LINE__ ,fname);
        free(fname);
        return 3;
    }
    /* free(fname); */
    return 0;
}

int
mode_build()
{
    fprintf(flog , "%s:%d ! Building database \"%s\"\n", __FILE__, __LINE__ ,qa->build);
    int r = 0;

    if ((r=create_file(get_db_filename(qa->build, STUD_EXT)))==0) {}
    else return r;
    if ((r=create_file(get_db_filename(qa->build, TOPIC_EXT)))==0) {}
    else return r;
    if ((r=create_file(get_db_filename(qa->build, LECTURER_EXT)))==0) {} else return r;

    return 0;
}

int spp_run ()
{
    switch (qa->mode) {
    case 0:
        break;

    case 1:                    /* add */
        return mode_add ();
        break;

    case 2:                    /* rm */
        return mode_rm ();
        break;

    case 3:                    /* show-links */
        return mode_show_links ();
        break;


    case 4:                    /* cat */
        return mode_cat ();
        break;

    case 5:                    /* edit */
        return mode_edit ();
        break;
    case 8:                     /* create */
        return mode_build();
        break;

    }

    return 0;
}

/* vim: set expandtab tabstop=4 shiftwidth=4: */
