<h1 align="center">
	🚀 Containers
</h1>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/JBVer/Containers?color=lightblue" />
	<img alt="Number of lines of code" src="https://tokei.rs/b1/github/JBVer/Containers?category=code" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/JBVer/Containers?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/JBVer/Containers?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/JBVer/Containers?color=green" />
</p>

## 💡 About the project

- Containers is a C++ project focused on re-implementing core C++ standard containers (vector, map, stack and set) in adherence to the C++98 standard.

## Testing


```shell
# This command runs custom container tests and records the results in the 'custom' file.
g++ tests.cpp && ./a.out > custom && rm a.out

# The same tests from the standard C++ containers. Output stored in the 'standard' file
g++ -D STANDARD=1 tests.cpp && ./a.out > standard && rm a.out

# Displays the difference between the two outputs
diff custom standard
```