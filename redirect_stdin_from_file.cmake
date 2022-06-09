  execute_process(
    COMMAND "${COMMAND}"
    INPUT_FILE "${INPUT_FILE}"
    OUTPUT_FILE "${OUTPUT_FILE}"
    RESULT_VARIABLE ret
  )
  if(ret)
    message(FATAL_ERROR "ERROR: ${COMMAND} failed: ${ret}")
  endif()
