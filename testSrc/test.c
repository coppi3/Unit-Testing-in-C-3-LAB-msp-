#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h> 
#include <stdint.h>
#include <string.h>
#include "plugin_api.h"
#include <stdio.h>
#define UNIT_TESTING 1

#define UNUSED(x) (void)(x)


// plugin get info test functions
static int get_info_setup(void **state) {
    struct plugin_info* pi;
    pi = malloc(sizeof(struct plugin_info));
    if (pi == NULL) {
        return -1;
    }

    int ret = plugin_get_info(pi);

    if (ret != 0) {
        return -1;
    }

    *state = pi;

    return 0;
}

static int get_info_teardown(void **state) {
    free(*state);

    return 0;
}


static void test_plugin_get_info_return_val(void **state) {
    assert_non_null(*state);
}

static void test_plugin_get_info_return_struct(void **state) {
    struct plugin_info* pi = *state;
    assert_string_equal("Check if a file contains a specified IPv4 address",pi->plugin_purpose);
    assert_string_equal("TEAMfromBIT",pi->plugin_author);
}

static void test_plugin_get_info_opts(void **state) {
    struct plugin_info* pi = *state;
    assert_in_range(pi->sup_opts_len,1,(((uintmax_t)-1)<<1)+1);
}

static void test_plugin_get_info_opts_pointer(void **state) {
    struct plugin_info* pi = *state;
    assert_non_null(pi->sup_opts);
}

// get info test end

// mockup libc functions




FILE* __wrap_fopen(const char *restrict pathname, const char *restrict mode);
FILE* __wrap_fopen(const char *restrict pathname, const char *restrict mode) {
    
    check_expected_ptr(pathname);

    check_expected_ptr(mode);

    return (FILE*)mock();
}

size_t __wrap_fread(void *restrict ptr, size_t size, size_t nmemb, FILE * stream);
size_t __wrap_fread(void *restrict ptr, size_t size, size_t nmemb, FILE * stream) {
    
    check_expected(size);

    check_expected(nmemb);

    check_expected(stream);

    unsigned int magicnum;

	magicnum = mock();

    memcpy(ptr,&magicnum,sizeof(unsigned int));

    return 1;

}

int __wrap_fclose(FILE *stream); 
int __wrap_fclose(FILE *stream) {

    check_expected(stream);

    return 0;
}

//mockup libc functions end
//Checking if convert_to_IPv4() func works correctly
static void test_convert_to_IPv4(void ** state){
    UNUSED(state);

    char resultChar_mocked[5];
    char * address_mocked = "127.0.0.1";

    resultChar_mocked[0] = 127;
    resultChar_mocked[1] = 0;
    resultChar_mocked[2] = 0;
    resultChar_mocked[3] = 1;
    resultChar_mocked[4] = 0;
    
    char * resultChar_real = convert_to_IPv4(address_mocked);
    assert_string_equal(resultChar_real, resultChar_mocked);
}
//char * p = memmem(fileContents, st.st_size + 1, ipv4_bytes, 4);
//Checking if memmem() func works correctly
static void test_memmem(void ** state){
    UNUSED(state);

    //char resultChar_mocked[5];
    
    char  *address_mocked = "POSTAVTEZACHOT"; // V
    int lenresult_mocked=strlen(address_mocked);
    char *find="VTEZACHOT";

    int lenfind=strlen(find);

    char *resultChar_real=memmem(address_mocked,lenresult_mocked,find,lenfind);


    assert_non_null(&resultChar_real);
    
}


//process file tests

static void test_plugin_process_file_gif(void **state) {
    UNUSED(state);

    struct option in_opts[] = {{"pic", 0, (int*)"gif",0}};
        
    

    unsigned int gif = 0x38464947;

    char* path = "/root/pic.gif";

    FILE* file = (FILE*)0xff035532a;


//    expect_string(__wrap_fopen, pathname, path); 
    expect_string(__wrap_fopen, pathname, path); 

    expect_string(__wrap_fopen, mode, "rb");

    will_return(__wrap_fopen, file);

    expect_value(__wrap_fread, size, sizeof(int));

    expect_value(__wrap_fread, nmemb, 1);

    expect_value(__wrap_fread, stream, file);

    will_return(__wrap_fread, gif);

	expect_value(__wrap_fclose, stream, file);

    int ret = plugin_process_file(path, in_opts, 1);


    assert_int_equal(ret, 0);
    
}

static void test_plugin_process_file_png(void **state) {
    UNUSED(state);

    struct option in_opts[] = {{"pic", 0, (int*)"png",0}};
        
    

    unsigned int gif = 0x474e5089;

    char* path = "/root/pic.png";

    FILE* file = (FILE*)0xff035532a;


//    expect_string(__wrap_fopen, pathname, path); 
    expect_string(__wrap_fopen, pathname, path); 

    expect_string(__wrap_fopen, mode, "rb");

    will_return(__wrap_fopen, file);

    expect_value(__wrap_fread, size, sizeof(int));

    expect_value(__wrap_fread, nmemb, 1);

    expect_value(__wrap_fread, stream, file);

    will_return(__wrap_fread, gif);

	expect_value(__wrap_fclose, stream, file);

    int ret = plugin_process_file(path, in_opts, 1);


    assert_int_equal(ret, 0);
    
}

int main(void) {
//    cmocka_set_message_output(CM_OUTPUT_XML);
    const struct CMUnitTest get_info_tests[] = {
        cmocka_unit_test(test_plugin_get_info_return_val),
        cmocka_unit_test(test_plugin_get_info_return_struct),
        cmocka_unit_test(test_plugin_get_info_opts),
        cmocka_unit_test(test_plugin_get_info_opts_pointer),

    };
    const struct CMUnitTest convert_to_IPv4_tests[] = {
        cmocka_unit_test(test_convert_to_IPv4),
    };
    const struct CMUnitTest memmem_tests[] = {
        cmocka_unit_test(test_memmem),
    };

    return cmocka_run_group_tests(get_info_tests, get_info_setup, get_info_teardown) & cmocka_run_group_tests(convert_to_IPv4_tests, NULL, NULL)
        & cmocka_run_group_tests(memmem_tests, NULL, NULL);
}


