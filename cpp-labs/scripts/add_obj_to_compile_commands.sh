#! /bin/bash

if [[ ! -f ./compile_commands.json ]]; then
    echo "[]" > ./compile_commands.json
fi

jq_req=". += [{ \"file\": \"$1\", \"directory\": \"$(pwd)\", \"command\": \"$2\" }]"
echo $(jq "$jq_req" compile_commands.json) > compile_commands.json
