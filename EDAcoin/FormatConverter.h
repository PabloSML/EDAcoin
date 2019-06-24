#pragma once

#include "nlohmann/json.hpp"
#include "Definitions.h"
#include "EDAMerkleBlock.h"

using json = nlohmann::json;


json Transactions2Json(TransactionS& t);

TransactionS Json2Transactions(json& j);

json EdaMerkleBlock2Json(EdaMerkleBlockS& b);

