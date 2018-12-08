#!/usr/bin/python3

import cs_grading
import cmake_problem
import setting
import os

source_dir = os.path.dirname(os.path.realpath(__file__))

RESULT_DIR = 'results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = os.path.join(source_dir, 'rubric', 'general.config')
RUBRIC_PALINDROME = os.path.join(source_dir, 'rubric', 'palindrome.config')
RUBRIC_STREAMS = os.path.join(source_dir, 'rubric', 'streams.config')
RUBRIC_SIMPLE_CHAR_MANAGER = os.path.join(source_dir, 'rubric', 'simple_char_manager.config')
RUBRIC_FLEX_CHAR_MANAGER = os.path.join(source_dir, 'rubric', 'flex_char_manager.config')
GRADE_REPORT_DIR = './'

HOMEWORK = cs_grading.Homework(
    1,
    RESULT_DIR,
    False,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)

P4 = cs_grading.Problem(HOMEWORK, 4, 'palindrome', 5)
P5 = cs_grading.Problem(HOMEWORK, 5, 'streams', 15)
P6pt1 = cs_grading.Problem(HOMEWORK, 6.1, 'simple_char_manager', 10)
P6pt2 = cs_grading.Problem(HOMEWORK, 6.2, 'flex_char_manager', 20)

P4.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P4.grade_problem(RUBRIC_GENERAL, RUBRIC_PALINDROME)
if setting.OPEN_RESULT:
    P4.open_result(text_editor=setting.TEXT_EDITOR)


P5.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P5.grade_problem(RUBRIC_GENERAL, RUBRIC_STREAMS)
if setting.OPEN_RESULT:
    P5.open_result(text_editor=setting.TEXT_EDITOR)

P6pt1.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P6pt1.grade_problem(RUBRIC_GENERAL, RUBRIC_SIMPLE_CHAR_MANAGER)
if setting.OPEN_RESULT:
    P6pt1.open_result(text_editor=setting.TEXT_EDITOR)

P6pt2.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P6pt2.grade_problem(RUBRIC_GENERAL, RUBRIC_FLEX_CHAR_MANAGER)
if setting.OPEN_RESULT:
    P6pt2.open_result(text_editor=setting.TEXT_EDITOR)


GRADER = cs_grading.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
cs_grading.generate_grade_report(HOMEWORK, GRADER, GRADE_REPORT_DIR, overwrite=True, logging_level=setting.LOGGING_LEVEL)
