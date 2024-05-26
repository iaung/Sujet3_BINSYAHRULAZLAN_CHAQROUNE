#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAILLE 100

char texte[TAILLE]; // declare a character array to store the text
int resultat = 0;

// function to remove accents from characters
void convertir_accents(char *chaine) {
	int i;
	int length = strlen(chaine);
	
	// define mappings for accented characters
	const char *accented = "àáâãäåèéêëìíîïòóôõöùúûü";
	const char *unaccented = "aaaaaaeeeeiiiiooooouuuu";
	
	for (i = 0; i < length; i++) {
		char c = chaine[i];
		// check if the character is accented
		const char *acc = strchr(accented, c);
		if (acc != NULL) {
			// replace accented character with the non-accented character
			int index = acc - accented;
			chaine [i] = unaccented[index];
		}
	}
}

// alphanumeric verification
int verifier_alphanumerique(const char *chaine) {
	int has_alpha = 0;
	int has_digit = 0;
	int length = strlen(chaine);
	
	for (int i = 0; i < length ; i++) {
		char c = chaine[i];
		// verifier si le character est un alphabet
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			has_alpha  = 1;
		} else if (c >= '0' && c <= '9') {
			has_digit = 1;
		}
	}
	
	// retourne c'est alphanumeric s'il y a au moins un alphabet et un chiffres
	return has_alpha && has_digit;
}

// function to read a message from the user
void message() {
	printf("Entrez du texte : ");
	fgets(texte, TAILLE, stdin);
	texte[strcspn(texte, "\n")] = '\0'; 
}

// function to verify if the text contains any special characters
void verifier() {
	int has_special = 0;
	
	for (int i = 0; texte[i] != '\0'; i++) { //travers la chaine jusqu'au but
		if (!isalnum(texte[i]) && !isspace(texte[i])) { //check for non-alphanumeric or non-space characters
		printf("%c est un caractère spécial.\n", texte[i]);
		has_special = 1;
		}
	}
	
	if (has_special == 0) {
		printf("Il n'y a aucun caractère spécial !\n");
	} 
	
	if (verifier_alphanumerique(texte)) {
		printf("Le texte est alphanumérique.\n");
	} else {
		printf("Le texte n'est pas alphanumérique.\n");
	}
}

// function to perform Caesar cipher encryption
void Cesar(char *message, int cleCesar) {
	printf("Message chiffré avec une cle de %d : ", cleCesar);
	
	for (int i = 0; message[i] != '\0'; i++) { // Traverse la chaine jusqu'au but
		if (isalpha(message[i])) { // Vérifiez si le caractère est une lettre de l'alphabet
			char base = islower(message[i]) ? 'a' : 'A'; // determiner la base 
			message[i] = (message[i] - base + cleCesar) % 26 + base; // applique le cesar
		}
		printf("%c", message[i]); //imprimer le character encrypte
	}
	printf("\n");
}

void Vigenere(char *message, char *cleVigenere) {
	int longeurCle = strlen(cleVigenere);
	int j = 0;
	printf("Message chiffré avec la clé '%s' : ", cleVigenere);
	for (int i = 0; message[i] != '\0'; i++) { //travers le string jusqu'au debut
		if (isalpha(message[i])) { // Vérifiez si le caractère est une lettre de l'alphabet
			char base = islower(message[i]) ? 'a' : 'A'; // determiner la base 
			int decalage = toupper(cleVigenere[j % longeurCle]) - 'A'; // calculer le décalage par rapport à la clé
			message[i] = (message[i] - base + decalage) % 26 + base; //applique le vigenere
			j++; // passer a la character suivante
		}
		printf("%c", message[i]); //imprimer le character encrypte
	}
	printf("\n");
}

//fonction pour assurer le legerement apres scanf
void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
	int choixChiffrement; //pour gerer le choix d'encryption
	int cleCesar; //pour gerer le cleCesar
	char cleVigenere[TAILLE]; //pour gerer le cleVigenere
	int useConvertAccents = 0; //pour determiner qu'il faut convertir ou pas
	
	printf("------ Bienvenue a notre programme MiniProjet C ------\n");
	printf("Voulez-vous convertir les accents (1 = oui, 0 = non) ? \n");
	scanf("%d", &useConvertAccents); //demande a l'utilisateur s'il veut convertir des accents
	clearInputBuffer();
	
	message(); //lit l'input de message
	if (useConvertAccents) {
		convertir_accents(texte); //convertir l'accents
	}
	verifier(); //verifie s'il y a des char speciaux
	
	//demander l'utilisateur
	printf("Quel chiffrement souhaitez-vous utiliser?\n"); //option pour choisir le methode d'encryption
	printf(" 1 : Chiffrement César\n");
	printf(" 2 : Chiffrement Vigenère\n");
	printf(" Votre choix : ");
	scanf("%d", &choixChiffrement);
	clearInputBuffer(); //clear the input buffer after scanning
	
	if (choixChiffrement == 1) {
		printf("Entrez la clé de chiffrement pour César : ");
		scanf("%d", &cleCesar); //lit le cle
		clearInputBuffer();	//Effacer le tampon d'entrée après scanf
		Cesar(texte, cleCesar); //appeler la fonction pour faire l'encryption
	} else if (choixChiffrement == 2) {
		printf("Entrez la clé de chiffrement pour Vigenère : ");
		fgets(cleVigenere, TAILLE, stdin); //lit le cle
		cleVigenere[strcspn(cleVigenere, "\n")] = '\0'; //supprimer le caractère de nouvelle ligne
		Vigenere(texte, cleVigenere) ; //appeler la fonction pour faire l'encryption
	} else {
		printf("Choix invalide. Veuillez choisir 1 ou 2.\n"); //choix invalide
	}
	
	return 0; //terminer la fonction main
}
	
	
