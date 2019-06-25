#pragma once

#include "nlohmann/json.hpp"
#include "Definitions.h"
#include "EDAMerkleBlock.h"

using json = nlohmann::json;


json Transactions2Json(TransactionS& t);

TransactionS Json2Transactions(json& j);

json EdaMerkleBlock2Json(EdaMerkleBlockS& b);

EdaMerkleBlockS Json2EdaMerkleBlock(json& j);

json Block2Json(Model_Block& b);

Model_Block Json2Block(json& j);

json Header2Json(blockHeader& b);

blockHeader Json2Header(json& j);