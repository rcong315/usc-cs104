#!/usr/bin/python3

import cs_grading
import cmake_problem
import setting
import os

source_dir = os.path.dirname(os.path.realpath(__file__))

RESULT_DIR = 'results/' # where test results are stored
GRADER_CONFIG = '../grader.txt'
RUBRIC_GENERAL = os.path.join(source_dir, 'rubric', 'general.config')
RUBRIC_CAVE = os.path.join(source_dir, 'rubric', 'cave.config')
RUBRIC_FUNCTOR = os.path.join(source_dir, 'rubric', 'functor.config')
RUBRIC_MSORT = os.path.join(source_dir, 'rubric', 'msort.config')
RUBRIC_FATALIST = os.path.join(source_dir, 'rubric', 'fatalist.config')

GRADE_REPORT_DIR = './'

HOMEWORK = cs_grading.Homework(
    5,
    RESULT_DIR,
    False,
    detailed_results=setting.DETAILED_RESULT,
    compile_flags=setting.COMPILE_FLAGS,
    logging_level=setting.LOGGING_LEVEL,
)

P3 = cs_grading.Problem(HOMEWORK, 3, 'cave', 15)
P4a = cs_grading.Problem(HOMEWORK, 4.1, 'functor', 5)
P4b = cs_grading.Problem(HOMEWORK, 4.2, 'msort', 25)
P5 = cs_grading.Problem(HOMEWORK, 5, 'fatalist', 15)

for problem, rubric in [(P3, RUBRIC_CAVE), (P4a, RUBRIC_FUNCTOR), (P4b, RUBRIC_MSORT), (P5, RUBRIC_FATALIST)]:

    problem.generate_results(
        cmake_problem.cmake_problem,
        True,
        timeout=0,)
    if setting.GENERATE_GRADE_REPORT:
        problem.grade_problem(RUBRIC_GENERAL, rubric)
    if setting.OPEN_RESULT:
        problem.open_result(text_editor=setting.TEXT_EDITOR)


GRADER = cs_grading.Grader(GRADER_CONFIG, setting.LOGGING_LEVEL)
cs_grading.generate_grade_report(HOMEWORK, GRADER, GRADE_REPORT_DIR, overwrite=True, logging_level=setting.LOGGING_LEVEL)
