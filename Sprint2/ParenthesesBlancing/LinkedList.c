
/*************************************************************INCLUDEES********************************************/


#include "LinkedList.h"







/**********************************************************INCOMPLETE_DATATYPES**************************************/


/*  incomplete data type help to protect  linked list or stack
    hide implenetation of this struct from clients of this module 
    */
struct _node
{
  LinkedDataType_t data;
  struct _node *next;
};







/************************************************************APIS_IMPLEMENTATION*************************************/








/*
 * brief  :  this function used to return data of specific node 
 * param. : ( input )Pstr_head_ref  ponter  to the head of the  list 
 * param. : ( output )Data  ponter  to the verable that willreceive data  
 * return : (output )linkedlistStatus_t enum that indicate the status of the printing function  
 */
 
linkedlistStatus_t  LinkedList_Node_GetData (LinkedDataType_t * Data , pstr_Node_t  Pstr_head_ref , uint32_t position )
{
    
    uint32_t TempPos = 1 ;
    if((Pstr_head_ref == NULL )||(position == 0))
    {
        return LINKED_LIST_INIT_ERROR ;
    }
    else if(position == 1)
    {
        *Data = Pstr_head_ref->data ;
        return LINKED_LIST_OK ;
    }    
    else 
    {
    
        while(Pstr_head_ref->next != NULL)
        {
            Pstr_head_ref  = Pstr_head_ref->next ;
            TempPos++ ;
        }     
        if(TempPos < position )
        {
            return LINKED_LIST_DATA_ERREO ;
        }
        
        *Data = Pstr_head_ref->data ;
        return  LINKED_LIST_OK  ;
        
    }
    
    
    
    
}/* END_OF_FUN   LinkedList_Node_GetData() */




/*
 * brief  : this function used to print all data in the list (for debugging perpose )
 * param. : ( input )PPstr_head_ref  ponter  to the head of the  list 
 * return : (output )linkedlistStatus_t enum that indicate the status of the printing function  
 */
linkedlistStatus_t LinkedList_print (pstr_Node_t  Pstr_head_ref)
{
    uint32_t Counter =1 ;
    pstr_Node_t pstr_TempNode =  Pstr_head_ref ;
    while(pstr_TempNode != NULL)
    {
        printf("data of node %d is %d \n" , Counter++ , pstr_TempNode->data);
        pstr_TempNode = pstr_TempNode->next ;
    }
    
    
    
    return LINKED_LIST_OK ;
    
}/* END_OF_FUN LinkedList_print() */








/*
 * brief  : this function used to add node to start of the list 
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )new_data   data that you want to add   
 * return : (output )linkedlistStatus_t enum that indicate the status of the added node  
 */
 
 
linkedlistStatus_t LinkedList_add_node_to_the_front (LinkedDataType_t new_data, pstr_Node_t  *PPstr_head_ref)
{
    pstr_Node_t str_NewNode = NULL ; 
   
     /* check for input parameters and return an error id there is something wrong */
   
    if(PPstr_head_ref == NULL)
    {
        return LINKED_LIST_INIT_ERROR ;
    }
    
    
    str_NewNode  = (struct _node *)malloc(sizeof(struct _node));
    if(str_NewNode == NULL )/* always you need to check returned pointers from Allocation memory function before you start to use */
    {
        return LINKED_LIST_HEAP_ERROR ; 
    }
    
    
    str_NewNode->next = *PPstr_head_ref ;
    str_NewNode->data = new_data ;
    *PPstr_head_ref   = str_NewNode ;
    
    return LINKED_LIST_OK ;


}/* END_OF_FUN LinkedList_add_node_to_the_front() */








/*
 * brief  : this function used to add node to the end  of the list 
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )new_data   data that you want to add   
 * return : (output )linkedlistStatus_t enum that indicate the status of the added node  
 */
 
linkedlistStatus_t LinkedList_add_list_at_end ( LinkedDataType_t new_data ,pstr_Node_t  * PPstr_head_ref)
{
    pstr_Node_t  pstr_NewNode = NULL  , pstr_TempNode = * PPstr_head_ref; 
    
    
    /* check for input parameters and return an error id there is something wrong */
    if(PPstr_head_ref == NULL)
    {
        return LINKED_LIST_INIT_ERROR ;
    }    
    
    
    while((pstr_TempNode->next != NULL) &&(*PPstr_head_ref != NULL))    /* iterate until reach to the end of the list */
    {
        pstr_TempNode = pstr_TempNode->next ;
    }
    
    pstr_NewNode = (pstr_Node_t) malloc(sizeof(struct _node ));
    if(pstr_NewNode == NULL )   /* always you need to check returned pointers from Allocation memory function before you start to use */
    {
        return LINKED_LIST_HEAP_ERROR ;
    }
    
    pstr_TempNode->next = NULL ;
    pstr_TempNode->data = new_data ;
    
    pstr_TempNode->next = pstr_NewNode ;
    
    
    
    return LINKED_LIST_OK ;
    
    
    
}/* END_OF_FUN LinkedList_add_list_at_end() */






/*
 * brief  : this function used to add node to a specific location ( desired locations start from 1 )  
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )position   indicate which position you want to add 
 * param. : ( input )new_data   data that you want to add   
 * return : (output )linkedlistStatus_t enum that indicate the status of the added node  
 */
 
linkedlistStatus_t LinkedList_add_node_at_any_point ( LinkedDataType_t new_data , pstr_Node_t  * PPstr_head_ref , int position)
{
    uint32_t TempPos = 1 ;
    pstr_Node_t Pstr_Temp_node = *PPstr_head_ref , pstr_NewNode = NULL ;   
    
    
    /* check for input parameters and return an error id there is something wrong */
    if((PPstr_head_ref == NULL )||(position == 0))
    {
        return LINKED_LIST_INIT_ERROR ;
    }
    else if(( *PPstr_head_ref == NULL)||(position == 1))
    {
        return LinkedList_add_node_to_the_front(new_data ,PPstr_head_ref ) ;
    }

    pstr_NewNode = (pstr_Node_t) malloc(sizeof(struct _node));
    if(pstr_NewNode == NULL )
    {
        return LINKED_LIST_HEAP_ERROR ;
    }
    
    
    while((Pstr_Temp_node->next != NULL) && (TempPos++ < position-1))
    {
        Pstr_Temp_node  = Pstr_Temp_node->next ;
    }
    
    pstr_NewNode->next   = Pstr_Temp_node->next ;
    Pstr_Temp_node->next = pstr_NewNode ;
    pstr_NewNode->data   = new_data ;
    
    return LINKED_LIST_OK ;

    
    
}/* END_OF_FUN LinkedList_add_node_at_any_point() */







/*
 * brief  : this function used to delete node with a specific location ( desired locations start from 1 )  
 * param. : ( input )PPstr_head_ref  pointer to ponter  to the head of the linked list 
 * param. : ( input )node_position   indicate which position you want to delete 
 * return : (output )linkedlistStatus_t enum that indicate the status of the deleted node  
 */
 
linkedlistStatus_t LinkedList_delete_specific_node (pstr_Node_t * PPstr_head_ref, int node_position)
{
    int32_t TempPos = 1 ;
    pstr_Node_t Pstr_Temp_node = *PPstr_head_ref ,pstr_DeletNode = NULL ;
    
    /* check for input parameters and return an error id there is something wrong */
    if((PPstr_head_ref == NULL )||(node_position == 0)||(*PPstr_head_ref == NULL))  
    {
        return LINKED_LIST_INIT_ERROR ;
    }
    if(node_position == 1)  /* if postion == one this mean that we need to modify the head pointer of the list */
    {
        pstr_DeletNode = *PPstr_head_ref ;
        *PPstr_head_ref = (*PPstr_head_ref)->next ;
        free(pstr_DeletNode);
        pstr_DeletNode = NULL ;     /* required step to avoid dangiling pointer problem  */
        return LINKED_LIST_OK ;
    }

    while((Pstr_Temp_node->next->next != NULL) && (TempPos++ < node_position-1))    /*iterae until you reach to the desired node */ 
    {
        Pstr_Temp_node  = Pstr_Temp_node->next ;
    }
    if(--TempPos == node_position-1)     /* check if required location is not exisit */    
    {
        return LINKED_LIST_DATA_ERREO ;
    }
    pstr_DeletNode = Pstr_Temp_node->next ;
    Pstr_Temp_node->next = Pstr_Temp_node->next->next ;
    free(pstr_DeletNode);
    
    
    return LINKED_LIST_OK ;
    

    
}/* END_OF_FUN LinkedList_delete_specific_node() */



