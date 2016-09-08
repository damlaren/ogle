import subprocess
import sys

git_diff_output = subprocess.check_output(
	"git diff --name-only --diff-filter=ACM", universal_newlines=True)
git_diff_lines = git_diff_output.split("\n")

for file_name in git_diff_lines:
	if not file_name:
		continue
	print "Checking style for %s" %file_name
	ret_value = subprocess.call(
		"python 3rdparty/styleguide/cpplint/cpplint.py --filter="
    "-build/header_guard,-build/include_order,-legal/copyright,"
    "-build/c++11 %s"
		%file_name, stderr=subprocess.STDOUT)
	if ret_value != 0:
		sys.exit(ret_value)
sys.exit(0)
