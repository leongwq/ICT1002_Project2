/*
 * ICT1002 Assignment 2, 2017-18 Trimester 1.
 *
 * This file implements all of the functions for creating and manipulating
 * features.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campus1002.h"

/* declare your internal variables here */
FEATURE *head=NULL; // DO NOT EVER MODIFY IT


/*
 * Add a new feature
 *
 * Input:
 *   type - the type for new feature (one of FEATURE_*)
 *   id   - the identifier of the new feature
 *   name - the name of the new feature
 *   xloc - the x location of the new feature
 *   yloc - the y location of the new feature
 *   xdim - the x dimension of the new feature
 *   ydim - the y dimension of the new feature
 *
 * Returns:
 *   a pointer to the new FEATURE structure, if successful
 *   NULL, if memory could not be allocated
 */

FEATURE *features_add(char type, const char *id, const char *name, int xloc, int yloc, int xdim, int ydim) {

    FEATURE *ptr;

    ptr=(FEATURE*)malloc(sizeof(FEATURE));
    ptr->type = type;
    strcpy(ptr->id, id);
    strcpy(ptr->name, name);
    ptr->xloc = xloc;
    ptr->yloc = yloc;
    ptr->xdim = xdim;
    ptr->ydim = ydim;
    ptr->next=NULL;

    return ptr;
}


/*
 * Deallocate memory used by the current collection of features.
 */
void features_close() {
	
	/* to be implemented */
}


/*
 * Delete a feature from the collection.
 *
 * Input:
 *   feature - a pointer to the feature to be deleted
 */
void features_delete(FEATURE *feature) {
    
    FEATURE *ptr = feature;
    free(ptr); // Free the feature node from the misery of life
	
}

/*
 * Get a pointer to a feature with a given identifier.
 *
 * Input:
 *   id - the identifier to search for
 *
 * Returns:
 *   a pointer to the feature with the desired identifer, if it exists
 *   NULL, otherwise
 */

FEATURE *features_get(const char *id) {
	
    FEATURE *temp=head;
    
    while(temp!=NULL) {
        if(strcmp(temp->id,id) == 0) { // Loop till the ID matches
            return temp;
        }
        temp=temp->next; // Advance to the next node.
    }
    
    return NULL; // ID not found
}


/*
 * Initialise a new collection of features, deleting any existing collection.
 */
void features_init() {
	
	/* to be implemented */
}
 


/*
 * Print a summary of all of the features.
 */
void features_list() {
	
    FEATURE *temp=head; // Get the pointer of the head of linked list
    
    while(temp!=NULL) // Generated the map with the features
    {
        printf("%s\t\t%s",temp->id,temp->name);
        temp=temp->next;
    }
	
}


/*
 * Print the details of a feature.
 *
 * Input:
 *   feature - a pointer to the feature to be printed
 */
void features_print(FEATURE *feature) {
	
	/* to be implemented */
    
	
}


/*
 * Read a collection of features from a file and place them on the map.
 *
 * Input:
 *   f - the file
 *
 * Returns:
 *   the number of features read from the file, if successful
 *   ERROR_NOMEM, if there was memory allocation error
 *   ERROR_FILE, if there was a file error
 */
int features_read(FILE *f) {
	
	/* to be implemented */
	return 0;
	
}


/*
 * Check whether the proposed geometry of a feature conflicts with the
 * geometry of any other feature, that is, whether or not the rectangle
 * described by the xloc, yloc, xdim and ydim parameters overlaps with any
 * existing feature.
 *
 * If the id parameter is non-NULL, the feature with this identifier will
 * be ignored when checking for conflicts. This can be used when moving an
 * existing feature to new location.
 *
 * If the proposed geometry conflicts with that of at least one existing
 * feature, the function returns a pointer to one of those features. In
 * general, there may be more than one feature in conflict, and any of
 * these might be returned.
 *
 * Input:
 *   id - the identifier of the feature being checked
 *   xloc - the proposed x location
 *   yloc - the proposed y location
 *   xdim - the proposed x dimension
 *   ydim - the proposed y dimension
 *
 * Returns:
 *   NULL, if there are no existing features occuping this space
 *   a pointer to one of the features occupying this space, otherwise
 */
FEATURE *features_validate_geometry(const char *id, int xloc, int yloc, int xdim, int ydim) {
    FEATURE *temp=head; // Get the pointer of the head of linked list
    
    while(temp!=NULL) // Loop through all the nodes
    {
        if (xloc >= temp-> xloc && xloc <= (temp->xloc + temp->xdim)){ // Check if feature comflicts in x axis
            return temp; // Return the conflict feature pointer
        }
        else if (yloc >= temp-> yloc && yloc <= (temp->yloc + temp->ydim)){
            return temp; // Return the conflict feature pointer
        }
        temp=temp->next;
    }
	return NULL;
}


/*
 * Write the features to a file.
 *
 * Input:
 *   f - the file
 *
 * Returns:
 *   the number of features successfully written to the file, if successful
 *   ERROR_FILE, if there was a file error
 */
int features_write(FILE *f) {
	
	/* to be implemented */
	return 0;
	
}

