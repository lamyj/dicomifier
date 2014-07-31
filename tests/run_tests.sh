#!/bin/sh
DIRECTORY=`mktemp -d`

cat > ${DIRECTORY}/config  << EOF
HostTable BEGIN
remote = (REMOTE, localhost, 11112)
local = (LOCAL, localhost, 0)
HostTable END

AETable BEGIN
REMOTE ${DIRECTORY} RW (10, 1024mb) local
AETable END
EOF

dcmqrscp -c ${DIRECTORY}/config 11112 &
PID=$!

export DICOMIFIER_CALLING_AET=LOCAL
export DICOMIFIER_PEER_HOST=localhost
export DICOMIFIER_PEER_PORT=11112
export DICOMIFIER_PEER_AET=REMOTE

ctest --no-compress-output -T Test || true

kill ${PID}
rm -rf ${DIRECTORY}
