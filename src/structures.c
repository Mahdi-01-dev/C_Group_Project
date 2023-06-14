//
// Created by iu22 on 13/06/23.
//
#include <string.h>
#include <malloc.h>
#include "structures.h"


void freeNode(Node node) {
  free(node->memoryAddress);
  free(node->type);
  free(node->next);
  // Free each of the strings stored in args
  for (int i = 0; i < node->num; i++){
    free((node->args)[i]);
  }
  free(node->num);
}


Node createNode(uint8_t memoryAddress, const char* type, const char** args, uint8_t num) {
  Node newNode = malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("Malloc failed when allocating newNode");
    return NULL;
  }

  newNode->memoryAddress = memoryAddress;

  // Allocate memory for the type string and copy the content
  newNode->type = malloc(strlen(type) + 1);
  if (newNode->type == NULL) {
    printf("Malloc failed when allocating for type");
    free(newNode);
    return NULL;
  }
  strcpy(newNode->type, type);

  // Allocate memory for the args array
  newNode->args = malloc(sizeof(char *) * num);
  if (newNode->args == NULL) {
    printf("Malloc failed when allocating args list");
    free(newNode->type);
    free(newNode);
    return NULL;
  }

  // Allocate memory for each args element and copy string
  for (int i = 0; i < num; i++) {
    newNode->args[i] = malloc(strlen(args[i]) + 1);

    if (newNode->args[i] == NULL) {
      printf("arg[%d] malloc failed", i);
      // To free all the args before
      for (int j = 0; j < i; j++) {
        free(newNode->args[j]);
      }
      free(newNode->args);
      free(newNode->type);
      free(newNode);
      return NULL;
    }

    strcpy(newNode->args[i], args[i]);
  }


  newNode->num = num;
  newNode->next = NULL;

  return newNode;
}

