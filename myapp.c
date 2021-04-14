#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// Make them global

GtkWidget	*window;
GtkWidget	*fixed1;

GtkWidget	*button1;
GtkWidget	*start_button;

GtkWidget	*redo_button;

GtkWidget	*finish_button;

GtkWidget	*label1;
GtkWidget	*label2;
GtkWidget	*combo1;
GtkEntry	*entry1;

GtkWidget	*dialog1;
GtkWidget	*box1;
GtkWidget	*ok_button;
GtkListStore	*liststore2;

GtkEntry	*entry2;


GtkWidget	*radio1;
GtkWidget	*radio2;
GtkWidget	*radio3;

GtkBuilder	*builder; 


GtkWidget	*combo2;
GtkEntry	*entry3;
GtkListStore	*liststore1;

GtkWidget	*rateButton;
GtkWidget	*powerButton;
GtkWidget	*dupButton;

GtkWidget	*detImage;
GtkWidget	*detBox;

GtkWidget	*rezButton;
GtkWidget	*rezImage;
GtkWidget	*rezBox;
GtkWidget	*topLabel;
GtkWidget	*legendLabel;

int numberOfIterations = 1;
int numberOfRedos;

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk

//---------------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//---------------------------------------------------------------------
 
	builder = gtk_builder_new_from_file ("myapp.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
	combo1 = GTK_WIDGET(gtk_builder_get_object(builder, "combo1"));
	entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));

	dialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog1"));
	box1 = GTK_WIDGET(gtk_builder_get_object(builder, "box1"));
	ok_button = GTK_WIDGET(gtk_builder_get_object(builder, "ok_button"));
	liststore2 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore2"));

	entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));

	start_button = GTK_WIDGET(gtk_builder_get_object(builder, "start_button"));

	redo_button = GTK_WIDGET(gtk_builder_get_object(builder, "redo_button"));

	finish_button = GTK_WIDGET(gtk_builder_get_object(builder, "finish_button"));
	
	radio1 = GTK_WIDGET(gtk_builder_get_object(builder, "radio1"));
	radio2 = GTK_WIDGET(gtk_builder_get_object(builder, "radio2"));
	radio3 = GTK_WIDGET(gtk_builder_get_object(builder, "radio3"));

	combo2 = GTK_WIDGET(gtk_builder_get_object(builder, "combo2"));
	entry3 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
	liststore1 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

	rateButton = GTK_WIDGET(gtk_builder_get_object(builder, "rateButton"));
	powerButton = GTK_WIDGET(gtk_builder_get_object(builder, "powerButton"));
	dupButton = GTK_WIDGET(gtk_builder_get_object(builder, "dupButton"));
	
	detBox = GTK_WIDGET(gtk_builder_get_object(builder, "detBox"));
	detImage = GTK_WIDGET(gtk_builder_get_object(builder, "detImage"));
	
	rezBox = GTK_WIDGET(gtk_builder_get_object(builder, "rezBox"));
	rezImage = GTK_WIDGET(gtk_builder_get_object(builder, "rezImage"));
	legendLabel = GTK_WIDGET(gtk_builder_get_object(builder, "legendLabel"));
	rezButton = GTK_WIDGET(gtk_builder_get_object(builder, "rezButton"));
	topLabel = GTK_WIDGET(gtk_builder_get_object(builder, "topLabel"));

	gtk_widget_show(window);

	g_object_unref(G_OBJECT(builder));


	gtk_main();

	return EXIT_SUCCESS;

	}

//void	on_button1_clicked (GtkButton *b) {
	//gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "hey");

	//apelez script-ul cand apas pe buton
  //      char command1[1000];
	//strcpy( command1, "setsid sudo bash tryy.sh && exit" );
	
	// pun numele butonului in text si apoi il scriu intr-un fisier
	//const gchar *text = gtk_button_get_label (b);
	//snprintf(command1, sizeof(command1), "echo \"$(echo %s)\" > something.txt", text);
          //  system(command1);

	//pun in fisier si apoi citesc continutul fisierului si il pun in alt fisier
	//char str[999];
	//FILE * file;
	 // if ( (file = fopen("aux.txt", "w") ) == NULL )
  	//{
    	// printf("Error: can't create file") ;
    	// exit(1);
 	// }
	//fprintf(file,"%s",text);
	//fclose(file);
	//snprintf(command1, sizeof(command1), "echo \"$(cat %s)\" > something.txt", text);
            //system(command1);


	//}


//se apeleaza atunci cand in listsore (acel drop down list) se selecteaza o noua incapere pentru a fi testata
void	on_entry1_changed(GtkEntry *e) {

	gtk_widget_hide(redo_button); ///ascund butonul de redo
	
	gtk_widget_show(start_button); ///il fac vizibil pe cel de start

	char incapere[100];

	sprintf(incapere, "Doriti sa testati ''%s'' ?\nDaca da, apasati START si asteptati.", gtk_entry_get_text(e));
	gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

	}

//se apeleaza atunci cand apesi START pentru a incepe testarea
void on_start_button_clicked(GtkButton *b) {

	numberOfRedos = 1;  //pentru fiecare noua incapere,  reinitializez numarul de retestari

	char incapere[100];
	char command[100],command2[100],command3[100];
	FILE *finalFile, *auxFile;

	snprintf(command2, sizeof(command2), "echo %d > nr_deja_reluate.txt", numberOfRedos);
	system(command2);

        finalFile = fopen("rezultate_partiale.txt", "a");
        if (finalFile == 0)
        {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", finalFile, errno, strerror(errno));
        }

	auxFile = fopen("aux.txt", "w");
        if (auxFile == 0)
        {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", auxFile, errno, strerror(errno));
        }

        const gchar *buttonName = gtk_entry_get_text(entry1);
	snprintf(command3, sizeof(command), "echo %s > se_testeaza_acum.txt", buttonName);
	system(command3);

	snprintf(command, sizeof(command), "echo \"$(echo %s)\" >> rezultate_partiale.txt", buttonName);
	system(command);

	//pornesc testele apeland un script
	strcpy( command2, "setsid sudo bash testeaza.sh && exit" );
        //snprintf(command, sizeof(command), "echo (\"$(echo %s)\" > rezultate_finale.txt, buttonName ; echo da>rezultate_finale.txt)");	
	system(command2);
	

	if (numberOfRedos == numberOfIterations)
	{	
		//schimb textul label-ului
		sprintf(incapere, "Incaperea ''%s'' a fost testata 1 data.\nAlegeti o alta incapere.", gtk_entry_get_text(entry1));
		gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

		gtk_widget_hide(redo_button); ///ascund butonul de redo
	
		gtk_widget_show(start_button); ///il fac vizibil pe cel de start

	}
	else
	{
		//schimb textul label-ului pentru a anunta ca s-a efectuat testarea in incaperea selectata
		sprintf(incapere, "Incaperea ''%s'' a fost testata 1 data.\nVa rugam sa reluati testul!", gtk_entry_get_text(entry1));
		gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

		gtk_widget_hide(start_button); ///ascund butonul de start pentru a ramane doar cel de redo
	
		gtk_widget_show(redo_button); ///il fac vizibil pe cel de redo, care initial este ascuns
	}
	
	
	}


void on_ok_button_clicked(GtkButton *b2){
	char text_label[128], incapere[100];
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
	int ok;

	ok=1;
	sprintf(incapere, "%s\n", gtk_entry_get_text(entry2));	//incapere = ceea ce adaug in fisierul text


	FILE * file;
	  if ( (file = fopen("incaperi.txt", "a+") ) == NULL ) //deschid fisierul pentru append sau pentru read (a+)
  	{
    	 printf("Error: can't create file") ;
    	exit(1);
 	 }
	
	//verific ca incaperea pe care vreau sa o adaug sa nu fie deja introdusa
	while ((read = getline(&line, &len, file)) != -1) {
		if (!strcmp(line, incapere)) {
            		sprintf(text_label, "Incaperea ''%s'' a fost deja adaugata!\nIntroduceti o alta incapere!\n", gtk_entry_get_text(entry2)); // text_label = ceea ce pun in label
            		ok = 0;
			gtk_label_set_text (GTK_LABEL (label1), (const gchar* ) text_label); //schimb textul label-ului
			break;
		}
    	}

	//pun in fisierul "incaperi" incaprea adaugata, daca nu a fost adaugata anterior (daca ok==1)
	if (ok == 1) {
		fprintf(file,"%s",incapere);
		sprintf(text_label, "Incaperea \"%s\" a fost adaugata cu succes!\n", gtk_entry_get_text(entry2)); // text_label = ceea ce pun in label
		gtk_label_set_text (GTK_LABEL (label1), (const gchar* ) text_label); //schimb textul label-ului
	}

	fclose(file);
}


//dupa ce am adaugat toate incaperile, apas pe "Am terminat de adaugat incaperi"

void on_all_rooms_added_button_clicked(GtkButton *b3){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *line_without_enter;
    char text_label[100];
    char command[100];

    GtkTreeIter iter;
	
    fp = fopen("incaperi.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) { //iau toate incaperile adaugate in incaperi.txt 
	//printf("%s", line);
	line_without_enter = strtok(line,"\n"); //iau doar numele incaperii, fara \n
	gtk_list_store_append(liststore2, &iter);
	gtk_list_store_set(liststore2, &iter, 0, line, -1);	//si le append-ui in storelist 

    }

   sprintf(text_label, "Toate incaperile au fost adaugate!\nPuteti incepe testele!", gtk_entry_get_text(entry2)); // text_label = ceea ce pun in label
		gtk_label_set_text (GTK_LABEL (label1), (const gchar* ) text_label); //schimb textul label-ului
	
   strcpy(command,"echo 1 > nr_retestari.txt");
   system(command);	//pun initial 1 in nr_retestari, si daca nu se aleg 2 sau 3 retestari din radio buttons, ramane acest 1

}



///butnul ce reia testul pentru aceeasi incapere
void on_redo_button_clicked(GtkButton *b){

	char incapere[100];
	char command[1000];
	char command2[100];

	strcpy(incapere,gtk_entry_get_text(entry1)); ///pun in "incapere" numele incaperii luat din entry field

	numberOfRedos++; //numar de cate ori am testat aceeasi incapere
        
	snprintf(command2, sizeof(command2), "echo %d > nr_deja_reluate.txt", numberOfRedos);
	system(command2);

	//pornesc testele apeland un script
	strcpy( command, "setsid sudo bash testeaza.sh && exit" );
        //snprintf(command, sizeof(command), "echo (\"$(echo %s)\" > rezultate_finale.txt, buttonName ; echo da>rezultate_finale.txt)");	
	system(command);
	
	//schimb textul label-ului pentru a anunta ca s-a efectuat testarea in incaperea selectata
	sprintf(incapere, "Incaperea ''%s'' a fost retestata de %d ori.\nVa rugam sa reluati testul!", gtk_entry_get_text(entry1),numberOfRedos);
	gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

	
	if (numberOfRedos == numberOfIterations)  //daca am retestat deja de cate ori mi-am propus
	{

		gtk_widget_hide(redo_button); ///ascund butonul de redo pentru a ramane doar cel de redo
		gtk_widget_show(start_button); ///il fac vizibil pe cel de start, care initial este ascuns
	
		//schimb labelul
		sprintf(incapere, "Incaperea ''%s'' a fost retestata de %d ori.\nAlegeti o alta incapere.", gtk_entry_get_text(entry1),numberOfRedos);
		gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

        }


}


void	on_radio1_toggled(GtkRadioButton *b) {

	char command[100];
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));

	if (T) //daca radio1 e activ
	   numberOfIterations = 1;

	strcpy(command,"echo 1 > nr_retestari.txt");
	system(command);

	}

void	on_radio2_toggled(GtkRadioButton *b) {

	char command[100];
	FILE *nr_retestari;
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));

	if (T)
	   numberOfIterations = 2;

	strcpy(command,"echo 2 > nr_retestari.txt");
	system(command);


	}

void	on_radio3_toggled(GtkRadioButton *b) {

	char command[100];
	FILE *nr_retestari;
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) 
	   numberOfIterations = 3;

	strcpy(command,"echo 3 > nr_retestari.txt");
	system(command);

	}


void on_finish_button_clicked(GtkButton *b){

	char command[100], command2[100];
	FILE *fp;
	char * line = NULL;
        size_t len = 0;
	char *line_without_enter;
	ssize_t read;

	GtkTreeIter iter;

	strcpy(command,"sudo gcc cumuleaza_retestari.c -o cumuleaza; sudo ./cumuleaza rezultate_partiale.txt");
	system(command);

	strcpy(command2,"sudo gcc listeaza_toate_testele.c -o listeaza; sudo ./listeaza");
	system(command2);

	 fp = fopen("toate_testele.txt", "r");
  	 if (fp == NULL)
      		 exit(EXIT_FAILURE);

    	while ((read = getline(&line, &len, fp)) != -1) { //iau toate incaperile adaugate in toate_testele.txt 
		//printf("%s", line);
		line_without_enter = strtok(line,"\n"); //iau doar numele incaperii, fara \n
		gtk_list_store_append(liststore1, &iter);
		gtk_list_store_set(liststore1, &iter, 0, line, -1);	//si le append-ui in storelist 

    }


}

void on_rateButton_clicked(GtkButton *b){


	char incapere[100];
	char *aux_incapere;
	char *nr_test;
	char rata[10];
	char test[20];
	char line[100];
	char command[100], command1[100];

	strcpy(rata,"_rata_");

	sprintf(incapere, "%s\n", gtk_entry_get_text(entry3));	//iau ce am in drop down list, de ex: incapere_test1
	aux_incapere = strtok(incapere,"_"); // aux_incapere = "incapere"

	nr_test = strtok(NULL,aux_incapere);	//nr_test = _testX
	strcpy(test,nr_test);

	strcat(aux_incapere,rata); 	

	strcat(aux_incapere,test);	//voi avea ceva de genul: incapere_rata_testX 
	aux_incapere = strtok(aux_incapere,"\n"); //elimin \n	
	strcat(aux_incapere,".txt");	//am format numele fisierului 	

	printf("\n\n %s \n\n",aux_incapere);
	
	//ascund celelalte imagini
	gtk_widget_hide(detImage);

	//strcpy(command,"cp %s data.txt",aux_incapere);
	snprintf(command, sizeof(command), "cp %s data.txt",aux_incapere);
	system(command);
	
	//execut scriptul ce face plotul
	strcpy(command1, "setsid sudo gnuplot rata.p" );	
	system(command1);
	
	//afisez imaginea
	detImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (detBox), detImage);
	gtk_widget_show (detImage);
	gtk_widget_show (detBox);



}


void on_powerButton_clicked(GtkButton *b){


	char incapere[100];
	char *aux_incapere;
	char *nr_test;
	char rata[10];
	char test[20];
	char line[100];
	char command[100], command1[100];

	strcpy(rata,"_putere_");

	sprintf(incapere, "%s\n", gtk_entry_get_text(entry3));	//iau ce am in drop down list, de ex: incapere_test1
	aux_incapere = strtok(incapere,"_"); // aux_incapere = "incapere"

	nr_test = strtok(NULL,aux_incapere);	//nr_test = _testX
	strcpy(test,nr_test);

	strcat(aux_incapere,rata); 	

	strcat(aux_incapere,test);	//voi avea ceva de genul: incapere_rata_testX 
	aux_incapere = strtok(aux_incapere,"\n"); //elimin \n	
	strcat(aux_incapere,".txt");	//am format numele fisierului 	

	printf("\n\n %s \n\n",aux_incapere);
	
	//ascund celelalte imagini
	gtk_widget_hide(detImage);

	//strcpy(command,"cp %s data.txt",aux_incapere);
	snprintf(command, sizeof(command), "cp %s data.txt",aux_incapere);
	system(command);
	
	//execut scriptul ce face plotul
	strcpy(command1, "setsid sudo gnuplot putere.p" );	
	system(command1);
	
	//afisez imaginea
	detImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (detBox), detImage);
	gtk_widget_show (detImage);
	gtk_widget_show (detBox);


}



void on_dupButton_clicked(GtkButton *b){


	char incapere[100];
	char *aux_incapere;
	char *nr_test;
	char rata[10];
	char test[20];
	char line[100];
	char command[100], command1[100];

	strcpy(rata,"_dup_");

	sprintf(incapere, "%s\n", gtk_entry_get_text(entry3));	//iau ce am in drop down list, de ex: incapere_test1
	aux_incapere = strtok(incapere,"_"); // aux_incapere = "incapere"

	nr_test = strtok(NULL,aux_incapere);	//nr_test = _testX
	strcpy(test,nr_test);

	strcat(aux_incapere,rata); 	

	strcat(aux_incapere,test);	//voi avea ceva de genul: incapere_rata_testX 
	aux_incapere = strtok(aux_incapere,"\n"); //elimin \n	
	strcat(aux_incapere,".txt");	//am format numele fisierului 	

	printf("\n\n %s \n\n",aux_incapere);
	
	//ascund celelalte imagini
	gtk_widget_hide(detImage);

	//strcpy(command,"cp %s data.txt",aux_incapere);
	snprintf(command, sizeof(command), "cp %s data.txt",aux_incapere);
	system(command);
	
	//execut scriptul ce face plotul
	strcpy(command1, "setsid sudo gnuplot duplicate.p" );	
	system(command1);
	
	//afisez imaginea
	detImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (detBox), detImage);
	gtk_widget_show (detImage);
	gtk_widget_show (detBox);


}



void on_rezButton_clicked(GtkButton *b) {
	char command[1000];
	
	gtk_widget_hide(rezImage);///ascund imaginile
	strcpy(command, "setsid sudo gnuplot rezultat.p" );	
	system(command);
	
	//afisez imaginea
	rezImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (rezBox), rezImage);
	gtk_widget_show (rezImage);
	
	//pun in label incaperile
	FILE * fp;
    	char * line = NULL;
    	size_t len = 0;
    	ssize_t read;
    	char *line_without_enter;
    	char text_label[100];
	GtkTreeIter iter;
	
    	fp = fopen("incaperi.txt", "r");
    	if (fp == NULL)
        	exit(EXIT_FAILURE);

    	while ((read = getline(&line, &len, fp)) != -1) { //iau toate incaperile adaugate in incaperi.txt 
		//printf("%s", line);
		line_without_enter = strtok(line,"\n"); //iau doar numele incaperii, fara \n
		//gtk_list_store_append(legendLabel, &iter);
		gtk_label_set_text (GTK_LABEL (legendLabel), (const gchar* ) &iter); 
    	}
	
	
	gtk_widget_show (rezBox);
	gtk_widget_show (legendLabel);
	gtk_widget_hide(rezButton);///ascund butonul
}





