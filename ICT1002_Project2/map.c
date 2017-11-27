/*
 * ICT1002 Assignment 2, 2017-18 Trimester 1.
 *
 * This file implements all of the functions for creating and manipulating
 * the map.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "campus1002.h"

/* declare your internal variables here */
char fileName[20];
int xDimension = 0;
int yDimension = 0;


/*
 * Deallocate the current map.
 */
void map_close() {
	
    memset(fileName,0,strlen(fileName));
    xDimension = 0;
    yDimension= 0;
	
}

/*
 * Create a new empty map, erasing any existing map.
 *
 * Input:
 *   name - the name of the map
 *   xdim - the x dimension of the new map
 *   ydim - the y dimension of the new map
 *
 * Returns:
 *   0, if successful
 *   ERROR_NOMEM, if memory could not be allocated
 */
int map_init(const char *name, int xdim, int ydim) {
	
	//User input is now stored as internal variable
	strcpy(fileName, name);	
	xDimension = xdim;
	yDimension = ydim;

	// return *fileName;
	// return xDimension;
	// return yDimension;
    
    return 0;

}

/*
 * Print the map on the screen.
 */
void map_print() {
    
    char map[yDimension][xDimension]; // Generate 2D array for map
    memset( map, 0, sizeof(map));
    
    FEATURE *temp=head; // Get the pointer of the head of linked list

    while(temp!=NULL) // Generated the map with the features
    {
        for (int xdim = 0; xdim<temp->xdim; xdim++){
            map[temp->yloc][temp->xloc + xdim] = temp->type;
        }
        for (int ydim = 0; ydim<temp->ydim; ydim++){
            map[temp->yloc + ydim][temp->xloc] = temp->type;
        }
        temp=temp->next;
    }
    
    for (int i = 0; i < xDimension; i++) { // Print out the map
        for (int j = 0; j < yDimension; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}


/*
 * Add a feature to the map.
 *
 * This function does not check that the feature is in a valid location. Use
 * map_validate_geometry() and features_validate_geometry() to check that the
 * feaures lies within the map boundaries and does not conflict with any
 * other features, respectively, before invoking this function.
 *
 * Input:
 *   feature - a pointer to the feature structure to be added
 */
void map_put_feature(FEATURE *feature) {
    
    FEATURE *ptr = feature;
    FEATURE *temp=head;
    FEATURE *prev=NULL;
    
    FEATURE *conflictingPointer = features_validate_geometry(feature->id,feature->xloc,feature->yloc,feature->xdim,feature->ydim);
    int withinMap = map_validate_geometry(feature->xloc,feature->yloc,feature->xdim,feature->ydim);
    
    if (!withinMap){ // The feature is not within map
        printf("That location is not within map.\n");
        return;
    }
    
    if (conflictingPointer == NULL){ // Check if it has any conflicting features
        if(temp==NULL) { //Executes when linked list is empty
            ptr->next=NULL; // Sets next to NULL. (First node)
            head=ptr; // Set current head to ptr
        }
        else
        {
            while(temp!=NULL)
            {
                if(ptr->next == NULL) // Loop till the end of the the link
                {
                    prev=temp; // set prev ptr as current position
                    temp=temp->next; // Advance to the next node.
                    continue;
                }
                else
                {
                    //Insert the node
                    prev->next=ptr; // Set prev node next position to new old position
                    ptr->next=temp;
                }
            }
            //Insert node at last
            prev->next=ptr;
        }
    }
    else { // Conflicts with a pointer
        printf("That location is already occupied by feature %s.\n",conflictingPointer->name);
    }
}


/*
 * Create a map from a map record in a file.
 *
 * Input:
 *   f - the file
 *
 * Returns:
 *   0, if successful
 *   ERROR_NOMEM, if memory allocation failed
 *   ERROR_FILE, if there was a file error
 */
int map_read(FILE *f) {
	
    FEATURERAW feature;
    
    if (f == NULL) {
        printf("Could not open map.\n");
        return ERROR_FILE;
    }
    else {
        while (!feof(f)){
            fread(&feature,sizeof(feature),1,f);
            printf("%s\n",feature.name);
        }
    }
	return 0;
}


/*
 * Remove a feature from the map.
 *
 * Input:
 *   feature - a pointer to the feature structure to be removed
 */
void map_remove_feature(FEATURE *feature) {
    
    FEATURE *ptr = feature;
    FEATURE *prev=NULL;
    FEATURE *temp=head; // Get the head of the linked list
    
    if(temp!=NULL){
        while(temp!=NULL){
            if (temp == ptr){ // If the head is feature to be deleted
                features_delete(ptr);
                break;
            }
            else if(temp->next == ptr) // Loop till the feature pointer is found
            {
                prev = temp; // Get the node
                prev->next = ptr->next; // Set the previous node's next to the pointer's next
                features_delete(ptr);
                break;
            }
            temp=temp->next; // Advance to the next node.
        }

    }
    
}


/*
 * Check that a rectangle lies within the map boundaries.
 *
 * Input:
 *   xloc    - the x location of the rectangle
 *   yloc    - the y location of the rectangle
 *   xdim    - the x dimension of the rectangle
 *   ydim    - the y dimension of the rectangle
 *
 * Returns:
 *   0, if some part of the rectangle lies outside the map boundaries
 *   1, if the entire rectangle lies within the map boundaries
 */
int map_validate_geometry(int xloc, int yloc, int xdim, int ydim) {
	
    if ((xloc + xdim) > xDimension){
        return 0;
    }
    else if ((yloc + ydim) > yDimension){
        return 0;
    }
    
    return 1;
}

/*
 * Write the map record to a file.
 *
 * Input:
 *   f - the file
 *
 * Returns:
 *   ERROR_NONE, if writing was successful
 *   ERROR_FILE, otherwise
 */
int map_write(FILE *f) {
	
    FEATURERAW feature;
    
    if (f == NULL) {
        printf("error writing file !\n");
        return ERROR_FILE;
    }
    else {
        fwrite (&feature, sizeof(FEATURERAW), 1, f);
        printf("contents to file written successfully !\n");
    }
    fclose(f);
    return ERROR_NONE;
}
