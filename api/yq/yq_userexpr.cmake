################################################################################
##
##  YOUR QUILL
##
################################################################################

add_library(yq_userexpr SHARED
    userexpr/AlgebraString.cpp
    userexpr/RepoConfig.cpp
    userexpr/UserExpr.cpp

    userexpr/impl/Compiler.cpp
    userexpr/impl/Instruction.cpp
    userexpr/impl/Repo.cpp
    userexpr/impl/Streamline.cpp
    userexpr/impl/Symbol.cpp
    userexpr/impl/Token.cpp
    userexpr/impl/Tokenize.cpp
    userexpr/impl/VirtualMachine.cpp

    userexpr/opcode/AssignInstruction.cpp
    userexpr/opcode/ConstantInstruction.cpp
    userexpr/opcode/DuplicateInstruction.cpp
    userexpr/opcode/FunctionInstruction.cpp
    userexpr/opcode/OperatorInstruction.cpp
    userexpr/opcode/PopInstruction.cpp
    userexpr/opcode/ValueInstruction.cpp
    userexpr/opcode/VariableInstruction.cpp
)

target_link_libraries(yq_userexpr PUBLIC
    yq_core
    yq_math
)

LinkTest(yq_userexpr)

