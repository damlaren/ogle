import subprocess
import sys

git_diff_output = subprocess.check_output("git diff --name-only --diff-filter=ACM",
										  universal_newlines=True)
git_diff_lines = git_diff_output.split("\n")

for line in git_diff_lines:
	if not line:
		continue
	print "Checking style for %s" %line
	ret_value = subprocess.call("python 3rdparty/styleguide/cpplint/cpplint.py %s" %line,
								stderr=subprocess.STDOUT)
	if ret_value != 0:
		sys.exit(ret_value)
sys.exit(0)