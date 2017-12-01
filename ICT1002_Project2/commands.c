/*
 * ICT1002 Assignment 2, 2017-18 Trimester 1.
 *
 * This file implements all of the campus designer commands using the functions
 * provided in other files.
 *
 * All of the functions in this file (except do_file_command and
 * do_design_command) accept a single argument, being a string containing the
 * argument passed to the command. This string may be NULL or empty if the
 * command does not use an argument.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "campus1002.h"

char currentFeatureName[MAX_NAME];

/*
 * Execute a command in file mode.
 *
 * Input:
 *   command - a string containing the command (may be an empty string)
 *   arg - a string containing the argument (may be an empty string)
 *
 * Returns:
 *   0, if the program should continue
 *   1, if the command indicates that the interpreter should exit
 */
int do_file_command(const char *command, const char *arg) {

	int done = 0;	/* return value */

	if (command == NULL || strlen(command) == 0) {
		/* blank line; do nothing and return */
		return 0;
	}
	
	/* determine which command was given and execute the appropriate function */
	if (compare_token(command, "help") == 0)
		do_file_help(arg);
	else if (compare_token(command, "new") == 0)
		do_file_new(arg);
	else if (compare_token(command, "open") == 0)
		do_file_open(arg);
	else if (compare_token(command, "exit") == 0)
		done = 1;
	else
		printf("Unrecognised command: %s.\n", command);
	
	return done;
	
}


/*
 * File mode HELP command.
 */
void do_file_help(const char *arg) {
	
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "new") == 0)
		printf("NEW              Create a new design.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "open") == 0)
		printf("OPEN <filename>  Load a design from <filename>.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "exit") == 0)
		printf("EXIT             Leave the program.\n");
	
}

/*
 * File mode NEW command.
 */
void do_file_new(const char *arg) {

	char userName[20];
	int userXdim = 0;
	int userYdim = 0;

	// Check for user input
	printf("Enter a name for the new design: ");
	scanf(" %s", userName);
    getchar();
	printf("Enter the x dimension: ");
	scanf(" %d",&userXdim);
    getchar();
	printf("Enter the y dimension: ");
	scanf(" %d",&userYdim);
    getchar();


	// Store user input into variables in map.c for usage
	map_init(userName, userXdim, userYdim);

	//Once done, enter design mode
	main_design();
	
}

/*
 * File mode OPEN command.
 */
void do_file_open(const char *arg) {
	
    FILE *f = fopen(arg, "rb");
    if (map_read(f) == ERROR_NONE){
        main_design(); // Enter design mode
    }
    else {
        printf("Could not open map.\n");
    }
}

/*
 * Execute a command in design mode.
 *
 * Input:
 *   command - a string containing the command (may be an empty string)
 *   arg - a string containing the argument (may be an empty string)
 *
 * Returns:
 *   0, if the program should continue
 *   1, if the command indicates that the interpreter should exit
 */
int do_design_command(const char *command, const char *arg) {

	int done = 0;	/* return value */

	if (command == NULL || strlen(command) == 0) {
		/* blank line; do nothing and return */
		return 0;
	}
	
	/* determine which command was given and execute the appropriate function */
	if (compare_token(command, "help") == 0)
		do_design_help(arg);
	else if (compare_token(command, "add") == 0)
		do_design_add(arg);
	else if (compare_token(command, "delete") == 0)
		do_design_delete(arg);
    else if (compare_token(command, "deletefeatures") == 0)
        do_design_deletefeatures(arg);
	else if (compare_token(command, "display") == 0)
		do_design_display(arg);
	else if (compare_token(command, "list") == 0)
		do_design_list(arg);
	else if (compare_token(command, "move") == 0)
		do_design_move(arg);
	else if (compare_token(command, "resize") == 0)
		do_design_resize(arg);
	else if (compare_token(command, "rename") == 0)
		do_design_rename(arg);
	else if (compare_token(command, "save") == 0)
		do_design_save(arg);
	else if (compare_token(command, "exit") == 0)
		done = 1;
	else
		printf("Unrecognised command: %s.\n", command);
	
	return done;
}


/*
 * Design mode HELP command.
 */
void do_design_help(const char *arg) {
	
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "display") == 0)
		printf("DISPLAY          Show the current map.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "display") == 0)
		printf("DISPLAY <id>     Show the details of the feature with identifier <id>.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "add") == 0)
		printf("ADD <id>         Create a new feature with identifer <id>\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "delete") == 0)
		printf("DELETE <id>      Delete the feature with identifier <id>.\n");
    if (arg == NULL || arg[0] == '\0' || compare_token(arg, "delete") == 0)
        printf("DELETEFEATURES   Delete all features in the map.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "list") == 0)
		printf("LIST             List all of the features on the map.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "move") == 0)
		printf("MOVE <id>        Move the feature with identifier <id>.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "rename") == 0)
		printf("RENAME <id>      Rename the feature with identifier <id>.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "resize") == 0)
		printf("RESIZE <id>      Resize the feature with identifier <id>.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "save") == 0)
		printf("SAVE <filename>  Save the current map in <filename>.\n");
	if (arg == NULL || arg[0] == '\0' || compare_token(arg, "exit") == 0)
		printf("EXIT             Stop editing and return to file mode.\n");
	
}

/*
 * Design mode ADD command.
 */
void do_design_add(const char *arg) {
	
    char featureID[MAX_ID];
    char featureName[MAX_NAME];
    char featureType = '\0';
    int xLoc = 0;
    int yLoc = 0;
    int xDim = 0;
    int yDim = 0;
    
    strcpy(featureID, arg); // Set featureID
    
    while ((featureType != '#') && (featureType != '.') && (featureType != '_') && (featureType != '*')) {
        printf("Please enter a valid feature type.\n");
        printf("What type of feature?\n  # - building\n  . - green space\n  _ - road\n  * - walkway\n");
        featureType = getchar();
        getchar();
    }
    
    switch(featureType) {
        case '#':
            featureType = FEATURE_BUILDING;
            break;
        case '.':
            featureType = FEATURE_GREENSPACE;
            break;
        case '_':
            featureType = FEATURE_ROAD;
            break;
        case '*':
            featureType = FEATURE_WALKWAY;
            break;
    }
    
    printf("Enter a name for feature %s: ",arg);
    lscanf(" %s", featureName);
    printf("Enter the x location: ");
	scanf(" %d", &xLoc);
    getchar();
    printf("Enter the y location: ");
    scanf(" %d", &yLoc);
    getchar();
    printf("Enter the x dimension: ");
    scanf(" %d", &xDim);
    getchar();
    printf("Enter the y dimension: ");
    scanf(" %d", &yDim);
    getchar();
    
    strcpy(currentFeatureName, featureID); // Set current feature ID to global
    FEATURE *ptr;
    ptr = features_add(featureType, featureID, featureName, xLoc, yLoc, xDim, yDim); // Get the ptr for feature
    map_put_feature(ptr); // Add the feature on the map
}

/*
 * Design mode delete command.
 */
void do_design_delete(const char *arg) {
	
    FEATURE *temp=head;
    char *id;
    
    while(temp!=NULL) {
        id = temp->id; // Convert char to char* for comparision
        if(strcmp(temp->id,arg) == 0) { // Loop till the ID matches
            map_remove_feature(temp); // Pass the pointer of feature to be deleted
            printf("%s deleted \n",temp->id);
        }
        temp=temp->next; // Advance to the next node.
    }
}

/*
 * Design mode deletefeatures command.
 */
void do_design_deletefeatures(const char *arg) {
    
    features_close();
}

/*
 * Design mode DISPLAY command.
 */
void do_design_display(const char *arg) {
    
    if (arg == NULL){
        printf("Your map canvas:\n");
        map_print();
    }
    else {
        if (features_get(arg) == NULL){
            printf("Feature with ID: %s not found.\n",arg);
        }
        else {
            features_print(features_get(arg));
        }
    }
}

/*
 * Design mode LIST command.
 */
void do_design_list(const char *arg) {
	
    features_list();
}

/*
 * Design mode MOVE command.
 */
void do_design_move(const char *arg) {
    
    int newxLoc;
    int newyLoc;
	
	FEATURE *ptr = features_get(arg); // Get the pointer of the node to be moved
    
    if (ptr != NULL){
        printf("Enter new x location: ");
        scanf(" %d", &newxLoc);
        printf("Enter new y location: ");
        scanf(" %d", &newyLoc);
        
        FEATURE *conflictingPointer = features_validate_geometry(ptr->id,newxLoc,newyLoc,ptr->xdim,ptr->ydim); // Check if new location has any conflicts
        int withinMap = map_validate_geometry(newxLoc,newyLoc,ptr->xdim,ptr->ydim); // Check if new location is within map
        if (!withinMap){ // The feature is not within map
            printf("That location is not within map.\n");
            return;
        }
        
        if (conflictingPointer == NULL || conflictingPointer == ptr){ // Check if it has any conflicting features
            ptr->xloc = newxLoc;
            ptr->yloc = newyLoc;
            printf("Feature with ID: %s has been updated with new location.\n",arg);
        }
        else {
            printf("That location is already occupied by feature %s.\n",conflictingPointer->name);
        }
    }
    else {
        printf("Feature with ID: %s not found.\n",arg);
    }

	
}

/*
 * Design mode RENAME command.
 */
void do_design_rename(const char *arg) {
	
    char newFeatureName[MAX_NAME];
    FEATURE *ptr = features_get(arg); // Get the pointer of the node to be renamed
    if (ptr != NULL){
        printf("Enter a new name for the feature: ");
        scanf(" %s", newFeatureName);
        strcpy(ptr->name,newFeatureName); // Set the new name to feature
    }
    else {
        printf("Feature with ID: %s not found.\n",arg);
    }

}


/*
 * Design mode RESIZE command.
 */
void do_design_resize(const char *arg) {
	
    int newxDim;
    int newyDim;
    
    FEATURE *ptr = features_get(arg); // Get the pointer of the node to be moved
    
    if (ptr != NULL){
        printf("Enter new x dimension: ");
        scanf(" %d", &newxDim);
        printf("Enter new y dimension: ");
        scanf(" %d", &newyDim);
        
        FEATURE *conflictingPointer = features_validate_geometry(ptr->id,ptr->xloc,ptr->yloc,newxDim,newyDim); // Check if new dimension has any conflicts
        int withinMap = map_validate_geometry(ptr->xloc,ptr->yloc,newxDim,newyDim); // Check if new dimension is within map
        if (!withinMap){ // The feature is not within map
            printf("That dimension is not within map.\n");
            return;
        }
        
        if (conflictingPointer == NULL || conflictingPointer == ptr){ // Check if it has any conflicting features
            ptr->xdim = newxDim;
            ptr->ydim = newyDim;
            printf("Feature with ID: %s has been updated with new dimension.\n",arg);
        }
        else {
            printf("That location is already occupied by feature %s.\n",conflictingPointer->name);
        }
    }
    else {
        printf("Feature with ID: %s not found.\n",arg);
    }
}

/*
 * Design mode SAVE command.
 */
void do_design_save(const char *arg) {
	
    FILE *f = fopen(arg, "w");
    map_write(f);
	
}
