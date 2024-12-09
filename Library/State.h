#pragma once

#include "Condition.h"
#include "UtilityCommands.h"
#include <initializer_list>
#include <list>
#include <functional>

using F = bool(void);

template <typename C> struct Transition;
template <typename C> struct State;

template <typename C> struct State {
  std::list<Transition<C>> transitions;

  State<C>(std::initializer_list<Transition<C>> transitions) : transitions(transitions) {}
};

template <typename C>
State(std::initializer_list<Transition<C>>) -> State<C>;

template <typename C> struct Transition {
  std::function<bool(Context ctx)> cond;
  std::list<int> actuatorPushCmds;
  std::list<int> actuatorPopCmds;
  std::list<UtilityCommand> utilityPushCmds;
  std::list<int> utilityPopCmds;
  State<C> *targetState;

  Transition<C>(std::function<bool(Context ctx)> cond, std::list<int> actuatorPushCmds,
                std::list<int> actuatorPopCmds,
                std::list<UtilityCommand> utilityPushCmds,
                std::list<int> utilityPopCmds,
                State<C> *targetState)
      : condPointer(condPointer), actuatorPushCmds(actuatorPushCmds),
        actuatorPopCmds(actuatorPopCmds), utilityPushCmds(utilityPushCmds),
        utilityPopCmds(utilityPopCmds), targetState(targetState) {}
};

template <typename C>
Transition(std::function<bool(Context ctx)>, std::list<int>,
           std::list<int>, std::list<UtilityCommand>,
           std::list<int>, State<C> *) -> Transition<C>;

