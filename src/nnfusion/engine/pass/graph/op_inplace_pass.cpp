// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "op_inplace_pass.hpp"
#include "nnfusion/core/graph/gnode.hpp"
#include "nnfusion/core/graph/graph.hpp"
#include "nnfusion/core/operators/generic_op/generic_op.hpp"
#include "nnfusion/core/operators/op_define/broadcast.hpp"
#include "nnfusion/core/operators/op_define/reduce.hpp"
#include "nnfusion/core/operators/op_define/reshape.hpp"
#include "nnfusion/core/operators/op_define/result.hpp"
#include "nnfusion/core/operators/op_define/select.hpp"
#include "nnfusion/core/operators/util/arithmetic_reduction.hpp"
#include "nnfusion/core/operators/util/elementwise_arithmetic.hpp"

using namespace nnfusion::graph;
using namespace nnfusion::op;
using namespace nnfusion::pass::graph;

bool OpInplacePass::run_on_graph(std::shared_ptr<Graph>& graph)
{
    for (auto node : graph->get_nodes())
    {
        if (auto op = std::dynamic_pointer_cast<Result>(node->get_op_ptr()))
        {
            AddInplace(op, 0, 0, false);
        }

        else if (auto op = std::dynamic_pointer_cast<ElementwiseArithmetic>(node->get_op_ptr()))
        {
            AddInplace(op, 0, 0, true);
        }

        else if (auto op = std::dynamic_pointer_cast<Select>(node->get_op_ptr()))
        {
            AddInplace(op, 0, 1, true);
        }

        else if (node->get_op_type() == "AddN")
        {
            auto op = std::dynamic_pointer_cast<GenericOp>(node->get_op_ptr());
            AddInplace(op, 0, 0, true);
        }

        else if (node->get_op_type() == "ApplyGradient")
        {
            auto op = std::dynamic_pointer_cast<GenericOp>(node->get_op_ptr());
            AddInplace(op, 0, 0, false);
        }
    }
    return true;
}
