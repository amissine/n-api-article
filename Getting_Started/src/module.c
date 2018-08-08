#include "./module.h"

napi_value MyFunction(napi_env env, napi_callback_info info) {
  napi_status status;

  /* Get the expected arguments. Here, we expect one Javascript object o.
   */
  size_t argc = 1, argcExpected = argc;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }
  fprintf(stderr, "argcExpected=%zu argc=%zu\n", argcExpected, argc);

  /* Get o.namespace property.
   */
  napi_value ns_key, ns_value;
  status = napi_create_string_utf8(env, "namespace", NAPI_AUTO_LENGTH, &ns_key);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to set napi_value ns_key");
  }
  status = napi_get_property(env, argv[0], ns_key, &ns_value);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to set napi_value ns_value");
  }
  char namespace[NAMESPACE_MAXLENGTH + 1];
  size_t ns_length;
  status = napi_get_value_string_utf8(env, ns_value, namespace, sizeof(namespace), &ns_length);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to set the namespace value");
  }
  fprintf(stderr, "ns_length=%zu namespace='%s'\n", ns_length, namespace);

  /* Calculate the delta in microseconds.
   */
  long long int number = uDelta(namespace);
  napi_value myNumber;
  status = napi_create_int64(env, number, &myNumber);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create return value");
  }

  return myNumber;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, NULL, 0, MyFunction, NULL, &fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }

  status = napi_set_named_property(env, exports, "uDelta", fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
