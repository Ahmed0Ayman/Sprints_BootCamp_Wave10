
#ifndef __LINKED_LIST__
#define __LINKED_LIST__


/*************************************************************INCLUDEES********************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>


/*************************************************************CONSTANTS********************************************/


/* all linked list return status you need to chect the return data id isn't LINKED_LIST_OK then debug your code  */
typedef enum  { LINKED_LIST_OK =0 , LINKED_LIST_HEAP_ERROR , LINKED_LIST_INIT_ERROR , LINKED_LIST_DATA_ERREO }linkedlistStatus_t; 



/*************************************************************TYPEDEFS*********************************************/


/* to allow all clinet to create a pointer to imcomplete struct */
typedef struct _node  * pstr_Node_t  ;


/* make this module support wide range of datatype with minor change in implementation */
typedef uint8_t  LinkedDataType_t ;






/******************************************************APIS_DECLARATIONS********************************************/







/*
 * brief  : this function used to print all data in the list (for debugging perpose )
 * param. : ( input )PPstr_head_ref  ponter  to the head of the linked list 
 * return : (output )linkedlistStatus_t enum that indicate the status of the printing function  
 */
linkedlistStatus_t LinkedList_print (pstr_Node_t Pstr_head_ref);



/*
 * brief  : this function used to add node to start of the list 
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )new_data   data that you want to add   
 * return : (output )linkedlistStatus_t enum that indicate the status of the added node  
 */
linkedlistStatus_t LinkedList_add_node_to_the_front (LinkedDataType_t new_data, pstr_Node_t * PPstr_head_ref);





/*
 * brief  : this function used to add node to the end  of the list 
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )new_data   data that you want to add   
 * return : (output )linkedlistStatus_t enum that indicate the status of the added node  
 */
linkedlistStatus_t LinkedList_add_list_at_end ( LinkedDataType_t new_data , pstr_Node_t * PPstr_head_ref);





/*
 * brief  : this function used to add node to a specific location ( desired locations start from 1 )  
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )position   indicate which position you want to add 
 * param. : ( input )new_data   data that you want to add   
 * return : (output )linkedlistStatus_t enum that indicate the status of the added node  
 */
linkedlistStatus_t LinkedList_add_node_at_any_point (LinkedDataType_t new_data , pstr_Node_t  * PPstr_head_ref , int position);






/*
 * brief  : this function used to delete node with a specific location ( desired locations start from 1 )  
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )node_position   indicate which position you want to delete 
 * return : (output )linkedlistStatus_t enum that indicate the status of the deleted node  
 */
 

linkedlistStatus_t LinkedList_delete_specific_node (pstr_Node_t  * PPstr_head_ref, int node_position);





/*
 * brief  :  this function used to return data of specific node 
 * param. : ( input )Pstr_head_ref  ponter  to the head of the  list 
 * param. : ( output )Data  ponter  to the verable that willreceive data  
 * return : (output )linkedlistStatus_t enum that indicate the status of the printing function  
 */
 
linkedlistStatus_t  LinkedList_Node_GetData (LinkedDataType_t * Data , pstr_Node_t  Pstr_head_ref , uint32_t position );


#endif  /* __LINKED_LIST__ */