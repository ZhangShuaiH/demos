# 自动变化的变量，在不同rule中，值不同
auto-var : file1 file2 file3
	echo $^  # 右边所有文件 
	echo $<  # 右边第一个文件
	echo $?  # 右边更新的文件
	echo $@  # 左边的文件

# 失败后继续执行
test-:
	-exit 1 # 失败后继续执行
	echo good

# 打印内建及用户全局变量
global-var=global-var
vars:
	echo $(.VARIABLES)

# 条件表达式
if:
ifeq (var, val)
	echo equal
else
	echo not equal
endif

# todo
sort-var := sort-var1
sort-var:
	echo $(sort-var) # 有序变量
sort-var := sort-var2
unsort-var = unsort-var1
unsort-var:
	echo $(unsort-var) # 无序变量
unsort-var = unsort-var2

# recipe 与 rule 在同一行
inline-recipe: ; echo inline-recipe

# 变量值批量替换
sub-ref := a.o b.o l.a c.o
#sub-ref := $(patsubst %.o, %.c, $(sub-ref))
#sub-ref := $(sub-ref:.o=.c) 
sub-ref := $(sub-ref:%.o=%.c) 
substitute-reference:
	echo $(sub-ref)

# 默认变量
#con-var ?= con-var-default
ifeq ($(origin con-var), undefined)
con-var = con-var-default-ifeq
endif
condition-var:
	echo $(con-var)

# 调用 shell 命令
shell-out := $(shell find)
shell-out:
	echo $(shell-out)

# 包含换行符的变量 
define rule-var =
	echo rule-jjij
	echo rule-222
endef
rule:
	$(rule-var)

# 一些特殊变量
special-var:
	echo makefile_list: $(MAKEFILE_LIST)
	echo default_goal: $(DEFAULT_GOAL)
	echo make_resarts: $(MAKE_RESARTS)
	echo make_termout: $(MAKE_TERMOUT)
	echo make_termerr: $(MAKE_TERMERR)
	echo recipe_prefix: $(.RECIPEPREFIX)
	echo features:  $(.FEATURES)
	echo include_dirs: $(.INCLUDE_DIRS)
	-echo variables:  $(.VARIABLES)
	echo extra_prereqs: $(.EXTRA_PREREQS)
	echo cc: $(CC)
