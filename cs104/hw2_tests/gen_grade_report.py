#!/usr/bin/python3

import cs_grading
import cmake_problem
import setting
import os

source_dir = os.path.dirname(os.path.realpath(__file__))

RESULT_DIR = 'results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = os.path.join(source_dir, 'rubric', 'general.config')
RUBRIC_SELECTION_SORT = os.path.join(source_dir, 'rubric', 'selection_sort.config')
RUBRIC_CIRCULAR_LIST = os.path.join(source_dir, 'rubric', 'circular_list.config')
RUBRIC_DUCK_DUCK_GOOSE = os.path.join(source_dir, 'rubric', 'duck_duck_goose.config')
GRADE_REPORT_DIR = './'

HOMEWORK = cs_grading.Homework(
    2,
    RESULT_DIR,
    False,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)

P5 = cs_grading.Problem(HOMEWORK, 5, 'selection_sort', 10)
P6 = cs_grading.Problem(HOMEWORK, 6, 'circular_list', 20)
P7 = cs_grading.Problem(HOMEWORK, 7, 'duck_duck_goose', 20)

P5.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P5.grade_problem(RUBRIC_GENERAL, RUBRIC_SELECTION_SORT)
if setting.OPEN_RESULT:
    P5.open_result(text_editor=setting.TEXT_EDITOR)

P6.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P6.grade_problem(RUBRIC_GENERAL, RUBRIC_CIRCULAR_LIST)
if setting.OPEN_RESULT:
    P6.open_result(text_editor=setting.TEXT_EDITOR)

P7.generate_results(
    cmake_problem.cmake_problem,
    True,
    timeout=0,)
if setting.GENERATE_GRADE_REPORT:
    P7.grade_problem(RUBRIC_GENERAL, RUBRIC_DUCK_DUCK_GOOSE)
if setting.OPEN_RESULT:
    P7.open_result(text_editor=setting.TEXT_EDITOR)


GRADER = cs_grading.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
cs_grading.generate_grade_report(HOMEWORK, GRADER, GRADE_REPORT_DIR, overwrite=True, logging_level=setting.LOGGING_LEVEL)
