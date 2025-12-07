#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "stack.h"


void StackIsEmptyAfterInitialization(void){
    Stack stack;
    initStack(&stack);
    CU_ASSERT_EQUAL(stack.top, NULL);
}
//push
void TopValueIsCorrectAfterPush(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1337);
    CU_ASSERT_EQUAL(stack.top->data, 1337);

    push(&stack, 0);
    CU_ASSERT_EQUAL(stack.top->data, 0);

    push(&stack, -1);
    CU_ASSERT_EQUAL(stack.top->data, -1);
}

void TopValueIsCorrectAfterSeveralPush(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 0);
    push(&stack, 1);
    push(&stack, -2);
    
    CU_ASSERT_EQUAL(stack.top->data, -2);
}
//pop
void StackIsNullAfterPopSingleElement(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    pop(&stack);
    CU_ASSERT_EQUAL(stack.top, NULL);

}

void TopIsCorrectAfterPop(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 2);

    pop(&stack);

    CU_ASSERT_EQUAL(stack.top->data, 1);
    CU_ASSERT_PTR_NULL(stack.top->next);

}

void TopIsCorrectAfterPopFromNoneElementStack(void){
    Stack stack;
    initStack(&stack);

    pop(&stack);
    CU_ASSERT_PTR_NULL(stack.top);

}

// searchByValue
void SearchFindsExistingValue(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    
    Node* found = searchByValue(&stack, 2);
    CU_ASSERT_PTR_NOT_NULL(found);
    CU_ASSERT_EQUAL(found->data, 2);
}

void SearchReturnsNullForMissingValue(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 2);
    
    Node* notFound = searchByValue(&stack, 999);
    CU_ASSERT_PTR_NULL(notFound);
}

void SearchReturnsNullInEmptyStack(void){
    Stack stack;
    initStack(&stack);
    
    Node* result = searchByValue(&stack, 1);
    CU_ASSERT_PTR_NULL(result);
}

// searchByIndex
void SearchByIndexFindsTopElement(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 2);
    
    Node* top = searchByIndex(&stack, 0);
    CU_ASSERT_PTR_NOT_NULL(top);
    CU_ASSERT_EQUAL(top->data, 2);
}

void SearchByIndexFindsSecondElement(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 2);
    
    Node* second = searchByIndex(&stack, 1);
    CU_ASSERT_PTR_NOT_NULL(second);
    CU_ASSERT_EQUAL(second->data, 1);
}

void SearchByIndexReturnsNullForInvalidIndex(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    
    Node* result = searchByIndex(&stack, 5);
    CU_ASSERT_PTR_NULL(result);
}

// getTop
void GetTopReturnsNullForEmptyStack(void){
    Stack stack;
    initStack(&stack);
    
    const Node* top = getTop(&stack);
    CU_ASSERT_PTR_NULL(top);
}

void GetTopReturnsCorrectElement(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    
    const Node* top = getTop(&stack);
    CU_ASSERT_PTR_NOT_NULL(top);
    CU_ASSERT_EQUAL(top->data, 1);
}

// traverseStack 
void TraverseDoesNotCrashOnEmptyStack(void){
    Stack stack;
    initStack(&stack);
    
    traverseStack(&stack); 
}

void TraverseDoesNotCrashOnNonEmptyStack(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 2);
    
    traverseStack(&stack); 
}

// isEmpty
void IsEmptyReturnsTrueForEmptyStack(void){
    Stack stack;
    initStack(&stack);
    
    bool empty = isEmpty(&stack);
    CU_ASSERT_TRUE(empty);
}

void IsEmptyReturnsFalseForNonEmptyStack(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    
    bool empty = isEmpty(&stack);
    CU_ASSERT_FALSE(empty);
}

// destroyStack
void DestroyStackMakesTopNull(void){
    Stack stack;
    initStack(&stack);

    push(&stack, 1);
    push(&stack, 2);
    
    destroyStack(&stack);
    CU_ASSERT_EQUAL(stack.top, NULL);
}


int main(){
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Stack tests", 0, 0);

    CU_add_test(suite, "initStack", StackIsEmptyAfterInitialization);
    CU_add_test(suite, "Push single element", TopValueIsCorrectAfterPush);
    CU_add_test(suite, "Push several elements", TopValueIsCorrectAfterSeveralPush);

    CU_add_test(suite, "Pop from one-element stack", StackIsNullAfterPopSingleElement);
    CU_add_test(suite, "Pop from multiple-element stack", TopIsCorrectAfterPop);
    CU_add_test(suite, "Pop from none-element stack", TopIsCorrectAfterPopFromNoneElementStack);

    CU_add_test(suite, "Search finds existing value", SearchFindsExistingValue);
    CU_add_test(suite, "Search returns null for missing value", SearchReturnsNullForMissingValue);
    CU_add_test(suite, "Search returns null in empty stack", SearchReturnsNullInEmptyStack);
    
    CU_add_test(suite, "Search by index finds first", SearchByIndexFindsTopElement);
    CU_add_test(suite, "Search by index finds second", SearchByIndexFindsSecondElement);
    CU_add_test(suite, "Search by index null for invalid", SearchByIndexReturnsNullForInvalidIndex);
    
    CU_add_test(suite, "GetTop null for empty", GetTopReturnsNullForEmptyStack);
    CU_add_test(suite, "GetTop correct element", GetTopReturnsCorrectElement);
    
    CU_add_test(suite, "Traverse empty stack", TraverseDoesNotCrashOnEmptyStack);
    CU_add_test(suite, "Traverse non-empty stack", TraverseDoesNotCrashOnNonEmptyStack);
    
    CU_add_test(suite, "IsEmpty true for empty", IsEmptyReturnsTrueForEmptyStack);
    CU_add_test(suite, "IsEmpty false for non-empty", IsEmptyReturnsFalseForNonEmptyStack);
    
    CU_add_test(suite, "DestroyStack makes top null", DestroyStackMakesTopNull);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
}