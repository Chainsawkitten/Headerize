set(SRCS
        main.cpp
    )

set(HEADERS
        main.hpp
    )

create_directory_groups(${SRCS} ${HEADERS})

add_executable(Headerize ${SRCS} ${HEADERS})
