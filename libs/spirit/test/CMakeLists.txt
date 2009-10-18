#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
boost_additional_test_dependencies(spirit 
  BOOST_DEPENDS 
  test variant function_types intrusive 
  lambda assign iostreams math random dynamic_bitset fusion
  )

set(test_compile_flags "")

if(CMAKE_COMPILER_IS_GNUCC)
  set(test_compile_flags "-ftemplate-depth-300")
endif()

foreach(qi_run_test
    actions
    alternative
    attr
    attribute
    and_predicate
    binary
    bool
    char
    char_class
    difference
    end
    eps
    expect
    grammar
    int
    kleene
    lazy
    lexeme
    lit
    list
    match_manip
    match_manip_attr
    no_case
    not_predicate
    optional
    parse_attr
    permutation
    plus
    range_run
    raw
    real
    repeat
    rule
    sequence
    sequential_or
    skip
    symbols
    terminal_ex
    tst
    uint
    )
  boost_test_run(qi_${qi_run_test} qi/${qi_run_test}.cpp COMPILE_FLAGS ${test_compile_flags})
endforeach()

foreach(qi_compile_fail_test
    qi_grammar_fail
    qi_rule_fail)
  boost_test_compile_fail(${qi_compile_fail_test} qi/${qi_compiler_fail_test}.cpp 
    COMPILE_FLAGS ${test_compile_flags})
endforeach()

foreach(karma_run_test
    actions
    and_predicate
    alternative
    attribute
    binary
    bool
    buffer
    case_handling
    center_alignment
    char
    char_class
    delimiter
    eol
    eps
    format_manip
    format_manip_attr
    format_pointer_container
    generate_attr
    grammar
    int_numerics
    kleene
    lazy
    left_alignment
    list
    lit
    maxwidth
    not_predicate
    omit
    optional
    pattern
    pattern2
    plus
    real_numerics
    repeat
    right_alignment
    sequence
    stream
    tricky_alignment
    )
  boost_test_run(karma_${karma_run_test} karma/${karma_run_test}.cpp COMPILE_FLAGS ${test_compile_flags})
endforeach()

foreach(karma_compile_fail_test
    karma_grammar_fail
    karma_rule_fail)
  boost_test_compile_fail(${karma_compile_fail_test} 
    karma/${karma_compile_fail_test}.cpp 
    COMPILE_FLAGS ${test_compile_flags})
endforeach()

if(CMAKE_COMPILER_IS_INTEL)
  list(APPEND test_compile_flags "-no-vec")
endif()

foreach(lex_run_test
    lexertl1
    lexertl2
    lexertl3
    lexertl4
    lexertl5
    state_switcher_test
    lexer_state_switcher
    set_token_value
    dedent_handling_phoenix
    set_token_value_phoenix
    )
  boost_test_run(lex_${lex_run_test} lex/${lex_run_test}.cpp 
    COMPILE_FLAGS ${test_compile_flags})
endforeach()



