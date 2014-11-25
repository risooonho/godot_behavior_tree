#include "catch.hpp"
#include "utils.h"

TEST_CASE( "Behavior Tree", "[bt_comp]" ) {
    VirtualMachine vm;

    SECTION( "{R,[S,F,R],(F,+S,R)}->{S,[S,S,R],(R,+S,R)}->{F,[R,S,R],(F,+F,S)}" ) {
        MockFailureParallel parallel;
        MockSelector selector;
        MockSequence sequence;
        MockDecorator decorator;
        MockAction action[7];
        decorator.inner_node.children.push_back(action[5].inner_node);
        sequence.inner_node.children.push_back(action[1].inner_node);
        sequence.inner_node.children.push_back(action[2].inner_node);
        sequence.inner_node.children.push_back(action[3].inner_node);
        selector.inner_node.children.push_back(action[4].inner_node);
        selector.inner_node.children.push_back(decorator.inner_node);
        selector.inner_node.children.push_back(action[6].inner_node);
        parallel.inner_node.children.push_back(action[0].inner_node);
        parallel.inner_node.children.push_back(sequence.inner_node);
        parallel.inner_node.children.push_back(selector.inner_node);
        action[0].update_result = BH_RUNNING;
        action[1].update_result = BH_SUCCESS;
        action[2].update_result = BH_FAILURE;
        action[3].update_result = BH_RUNNING;
        action[4].update_result = BH_FAILURE;
        action[5].update_result = BH_SUCCESS;
        action[6].update_result = BH_RUNNING;
        to_vm(vm, parallel.inner_node);
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 1);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 1);
        REQUIRE(parallel.counter.child_update == 3);
        REQUIRE(sequence.child_update_result == BH_FAILURE);
        REQUIRE(sequence.counter.prepare == 1);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 1);
        REQUIRE(sequence.counter.child_update == 2);
        REQUIRE(selector.child_update_result == BH_SUCCESS);
        REQUIRE(selector.counter.prepare == 1);
        REQUIRE(selector.counter.abort == 0);
        REQUIRE(selector.counter.self_update == 1);
        REQUIRE(selector.counter.child_update == 2);
        REQUIRE(decorator.child_update_result == BH_SUCCESS);
        REQUIRE(decorator.counter.prepare == 1);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 1);
        REQUIRE(decorator.counter.child_update == 1);
        REQUIRE(action[0].counter.prepare == 1);
        REQUIRE(action[0].counter.abort == 0);
        REQUIRE(action[0].counter.self_update == 1);
        REQUIRE(action[0].counter.child_update == 0);
        REQUIRE(action[1].counter.prepare == 1);
        REQUIRE(action[1].counter.abort == 0);
        REQUIRE(action[1].counter.self_update == 1);
        REQUIRE(action[1].counter.child_update == 0);
        REQUIRE(action[2].counter.prepare == 1);
        REQUIRE(action[2].counter.abort == 0);
        REQUIRE(action[2].counter.self_update == 1);
        REQUIRE(action[2].counter.child_update == 0);
        REQUIRE(action[3].counter.prepare == 0);
        REQUIRE(action[3].counter.abort == 0);
        REQUIRE(action[3].counter.self_update == 0);
        REQUIRE(action[3].counter.child_update == 0);
        REQUIRE(action[4].counter.prepare == 1);
        REQUIRE(action[4].counter.abort == 0);
        REQUIRE(action[4].counter.self_update == 1);
        REQUIRE(action[4].counter.child_update == 0);
        REQUIRE(action[5].counter.prepare == 1);
        REQUIRE(action[5].counter.abort == 0);
        REQUIRE(action[5].counter.self_update == 1);
        REQUIRE(action[5].counter.child_update == 0);
        REQUIRE(action[6].counter.prepare == 0);
        REQUIRE(action[6].counter.abort == 0);
        REQUIRE(action[6].counter.self_update == 0);
        REQUIRE(action[6].counter.child_update == 0);
        action[0].update_result = BH_SUCCESS;
        action[1].update_result = BH_SUCCESS;
        action[2].update_result = BH_SUCCESS;
        action[3].update_result = BH_RUNNING;
        action[4].update_result = BH_RUNNING;
        action[5].update_result = BH_SUCCESS;
        action[6].update_result = BH_RUNNING;
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_SUCCESS);
        REQUIRE(parallel.counter.prepare == 2);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 2);
        REQUIRE(parallel.counter.child_update == 6);
        REQUIRE(sequence.child_update_result == BH_RUNNING);
        REQUIRE(sequence.counter.prepare == 2);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 2);
        REQUIRE(sequence.counter.child_update == 5);
        REQUIRE(selector.child_update_result == BH_RUNNING);
        REQUIRE(selector.counter.prepare == 2);
        REQUIRE(selector.counter.abort == 0);
        REQUIRE(selector.counter.self_update == 2);
        REQUIRE(selector.counter.child_update == 3);
        REQUIRE(decorator.counter.prepare == 1);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 1);
        REQUIRE(decorator.counter.child_update == 1);
        REQUIRE(action[0].counter.prepare == 1);
        REQUIRE(action[0].counter.abort == 0);
        REQUIRE(action[0].counter.self_update == 2);
        REQUIRE(action[0].counter.child_update == 0);
        REQUIRE(action[1].counter.prepare == 2);
        REQUIRE(action[1].counter.abort == 0);
        REQUIRE(action[1].counter.self_update == 2);
        REQUIRE(action[1].counter.child_update == 0);
        REQUIRE(action[2].counter.prepare == 2);
        REQUIRE(action[2].counter.abort == 0);
        REQUIRE(action[2].counter.self_update == 2);
        REQUIRE(action[2].counter.child_update == 0);
        REQUIRE(action[3].counter.prepare == 1);
        REQUIRE(action[3].counter.abort == 0);
        REQUIRE(action[3].counter.self_update == 1);
        REQUIRE(action[3].counter.child_update == 0);
        REQUIRE(action[4].counter.prepare == 2);
        REQUIRE(action[4].counter.abort == 0);
        REQUIRE(action[4].counter.self_update == 2);
        REQUIRE(action[4].counter.child_update == 0);
        REQUIRE(action[5].counter.prepare == 1);
        REQUIRE(action[5].counter.abort == 0);
        REQUIRE(action[5].counter.self_update == 1);
        REQUIRE(action[5].counter.child_update == 0);
        REQUIRE(action[6].counter.prepare == 0);
        REQUIRE(action[6].counter.abort == 0);
        REQUIRE(action[6].counter.self_update == 0);
        REQUIRE(action[6].counter.child_update == 0);
        action[0].update_result = BH_FAILURE;
        action[1].update_result = BH_RUNNING;
        action[2].update_result = BH_SUCCESS;
        action[3].update_result = BH_RUNNING;
        action[4].update_result = BH_FAILURE;
        action[5].update_result = BH_FAILURE;
        action[6].update_result = BH_SUCCESS;
        vm.tick(nullptr);
        REQUIRE(parallel.child_update_result == BH_FAILURE);
        REQUIRE(parallel.counter.prepare == 3);
        REQUIRE(parallel.counter.abort == 0);
        REQUIRE(parallel.counter.self_update == 3);
        REQUIRE(parallel.counter.child_update == 9);
        REQUIRE(sequence.child_update_result == BH_RUNNING);
        REQUIRE(sequence.counter.prepare == 2);
        REQUIRE(sequence.counter.abort == 0);
        REQUIRE(sequence.counter.self_update == 3);
        REQUIRE(sequence.counter.child_update == 6);
        REQUIRE(selector.child_update_result == BH_SUCCESS);
        REQUIRE(selector.counter.prepare == 2);
        REQUIRE(selector.counter.abort == 0);
        REQUIRE(selector.counter.self_update == 3);
        REQUIRE(selector.counter.child_update == 6);
        REQUIRE(decorator.counter.prepare == 2);
        REQUIRE(decorator.counter.abort == 0);
        REQUIRE(decorator.counter.self_update == 2);
        REQUIRE(decorator.counter.child_update == 2);
        REQUIRE(action[0].counter.prepare == 2);
        REQUIRE(action[0].counter.abort == 0);
        REQUIRE(action[0].counter.self_update == 3);
        REQUIRE(action[0].counter.child_update == 0);
        REQUIRE(action[1].counter.prepare == 2);
        REQUIRE(action[1].counter.abort == 0);
        REQUIRE(action[1].counter.self_update == 2);
        REQUIRE(action[1].counter.child_update == 0);
        REQUIRE(action[2].counter.prepare == 2);
        REQUIRE(action[2].counter.abort == 0);
        REQUIRE(action[2].counter.self_update == 2);
        REQUIRE(action[2].counter.child_update == 0);
        REQUIRE(action[3].counter.prepare == 1);
        REQUIRE(action[3].counter.abort == 0);
        REQUIRE(action[3].counter.self_update == 2);
        REQUIRE(action[3].counter.child_update == 0);
        REQUIRE(action[4].counter.prepare == 2);
        REQUIRE(action[4].counter.abort == 0);
        REQUIRE(action[4].counter.self_update == 3);
        REQUIRE(action[4].counter.child_update == 0);
        REQUIRE(action[5].counter.prepare == 2);
        REQUIRE(action[5].counter.abort == 0);
        REQUIRE(action[5].counter.self_update == 2);
        REQUIRE(action[5].counter.child_update == 0);
        REQUIRE(action[6].counter.prepare == 1);
        REQUIRE(action[6].counter.abort == 0);
        REQUIRE(action[6].counter.self_update == 1);
        REQUIRE(action[6].counter.child_update == 0);
    }
}
