#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"


char *lines_20 = "--------------------";
/*
#init_suit - the suite initialization function.
             Here we can do some stuff that help us durin a test, i.e try to
             open a file which we will be testing in our test function.
             Returns zero on success, non-zero otherwise.
*/
int init_suite(void)  { return 0; }

/*

#clean_suite - the suite cleanup function.
               Starts clean up procedure if there is somehing to be done,
               i.e. close a file, free memory etc.
               Returns zero on success, non-zero otherwise.
*/
int clean_suite(void) { return 0; }


int Return_One(){ return 1; }


void test_Return_One(){ CU_ASSERT(Return_One()== 1); }

int main(){

    CU_pSuite pSuite_1 = NULL, pSuite_2 = NULL;

    /* Initialize CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add suite to registry */
    pSuite_1 = CU_add_suite("Test_Suite_SQLite_DB_Creation", init_suite, clean_suite);
    if (NULL == pSuite_1) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    pSuite_2 = CU_add_suite("Test_Suite_SQLite_DB_Operations", init_suite, clean_suite);
    if (NULL == pSuite_2) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add tests to suite */
    if(
        /* testing reverse removing on left branch of tree*/
        (NULL == CU_add_test(pSuite_1, "test_1", test_Return_One))

        /* testind removing of particular node of tree */
    )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
/*
    if(

        (NULL == CU_add_test(pSuite_2, "test_Empty_Tree_Remove_Node", test_Empty_Tree_Remove_Node)) ||


    ){
        CU_cleanup_registry();
        return CU_get_error();
    }
*/

    /* Run tests using Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    /* Run all suits = run all tests */
    CU_basic_run_tests();
    /* Run specified suite */
    //CU_basic_run_suite(pSuite_1);
    //CU_basic_run_suite(pSuite_2);
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

/*
     // Run all tests using the automated interface - silence mode
    CU_automated_run_tests();
    CU_list_tests_to_file();
*/

    //Run all tests using the console interface - a new shell will be available
//    CU_console_run_tests();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
