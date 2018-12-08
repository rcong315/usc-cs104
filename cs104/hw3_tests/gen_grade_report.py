#!/usr/bin/python3

import cs_grading
import cmake_problem
import setting
import os

source_dir = os.path.dirname(os.path.realpath(__file__))

RESULT_DIR = 'results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = os.path.join(source_dir, 'rubric', 'general.config')
RUBRIC_STACK = os.path.join(source_dir, 'rubric', 'stack.config')
RUBRIC_ARITH_PARSER= os.path.join(source_dir, 'rubric', 'arith_parser.config')
GRADE_REPORT_DIR = './'

HOMEWORK = cs_grading.Homework(
    3,
    RESULT_DIR,
    False,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)

P4 = cs_grading.Problem(HOMEWORK, 4, 'stack', 10)
P5 = cs_grading.Problem(HOMEWORK, 5, 'arith_parser', 40)

P4.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P4.grade_problem(RUBRIC_GENERAL, RUBRIC_STACK)
if setting.OPEN_RESULT:
    P4.open_result(text_editor=setting.TEXT_EDITOR)


P5.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P5.grade_problem(RUBRIC_GENERAL, RUBRIC_ARITH_PARSER)
if setting.OPEN_RESULT:
    P5.open_result(text_editor=setting.TEXT_EDITOR)


GRADER = cs_grading.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
cs_grading.generate_grade_report(HOMEWORK, GRADER, GRADE_REPORT_DIR, overwrite=True, logging_level=setting.LOGGING_LEVEL)
