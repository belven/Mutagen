// Fill out your copyright notice in the Description page of Project Settings.

#include "Mutagen.h"
#include "Quest.h"
#include "QuestReward.h"
#include "QuestObjective.h"

/* Creates a new quest with the givin parameters, the last two are optional */
UQuest* UQuest::CreateQuest(AMutagenCharacter* character, TArray<UQuestObjective*> objectives, TArray<UQuestReward*> rewards){
	UQuest* tempQuest = ConstructObject<UQuest>(UQuest::StaticClass());
	tempQuest->SetOwner(character);
	tempQuest->SetObjectives(objectives);
	tempQuest->SetRewards(rewards);
	return tempQuest;
}

/* This is run by objectives to inform the quest that the objective has changed state */
void UQuest::ObjectiveUpdated(UQuestObjective* objective){
	if (objective->IsComplete() && IsComplete()){
		GiveRewards();
	}
}

/* Loops through all objectives and returns true if all are complete */
bool UQuest::IsComplete(){
	bool complete = true;

	for (UQuestObjective* objective : GetObjectives()){
		complete = objective->IsComplete() && complete;
	}

	return complete;
}

/* Adds a new objective to the quest */
void UQuest::AddObjective(UQuestObjective* inObjective){
	if (inObjective != NULL){
		objectives.Add(inObjective);
	}
}

/* Adds a new reward to the quest */
void UQuest::AddReward(UQuestReward* inReward){
	if (inReward != NULL){
		rewards.Add(inReward);
	}
}

/* Loops through the rewards giving the rewards to the quest owner */
void UQuest::GiveRewards(){
	if (GetOwner() != NULL){
		for (UQuestReward* reward : GetRewards()){
			if (reward != NULL){
				reward->GiveReward(GetOwner());
			}
		}
	}
}

TArray<UQuestReward*> UQuest::GetRewards(){
	return rewards;
}


void UQuest::SetRewards(TArray<UQuestReward*> newVal){
	rewards = newVal;
}


AMutagenCharacter* UQuest::GetOwner(){
	return owner;
}


void UQuest::SetOwner(AMutagenCharacter* newVal){
	owner = newVal;
}


TArray<UQuestObjective*> UQuest::GetObjectives(){
	return objectives;
}


void UQuest::SetObjectives(TArray<UQuestObjective*> newVal){
	objectives = newVal;
}