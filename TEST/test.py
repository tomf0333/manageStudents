import os
import subprocess


def compile_test():
    print("Running Tests")
    print("=========================================")

    print("Trying to compile file:")
    print("------------------------")
    compiled = subprocess.run(
        'gcc -Wextra -Wall -Wvla -std=c99 -lm manageStudents.c -o manageStudents',
        capture_output=True, text=True)

    assert (compiled.returncode == 0), "Program failed compiling"
    print("Program compiled successfully")


def general_test():
    for test in {"best", "merge", "quick"}:
        for file in os.listdir("infiles"):
            print("=============")
            print("Running test on " + test + " argument with file " + file)
            print("------------------------")

            with open("infiles/" + file.split(".")[0] + ".in") as inf:
                in_string = inf.read()
            with open(test + "out/" + file.split(".")[0] + ".out") as outf:
                out_string = outf.read()
            p1 = subprocess.run("manageStudents " + test, capture_output=True,
                                text=True, input=in_string)
            assert (p1.stdout == out_string), "Failed " + test +\
                                              " test. Output for " + file + \
                                              " file should be exactly" \
                                              " as specified in " + \
                                              file.split(".")[0] + ".out" + \
                                              " file\n=======\nOUTPUT WAS" \
                                              "\n=======\n" + p1.stdout
            print(test + " test passed!")


def run_tests():
    compile_test()
    general_test()


if __name__ == "__main__":
    run_tests()
