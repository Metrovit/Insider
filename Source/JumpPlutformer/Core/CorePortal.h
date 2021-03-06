#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorePortal.generated.h"

class UTexture;
class UBoxComponent;
class UStaticMeshComponent;
class APortalManager;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class APlayerCameraManager;

UCLASS()
class INSIDER_API ACorePortal : public AActor
{
	GENERATED_BODY()
	
public:	
	ACorePortal();

protected:

	virtual void BeginPlay() override;

public:	

	//Render Target to use  to display the portal
	UFUNCTION()
	void ClearRTT();

	UFUNCTION()
	void SetRTT(UTexture* RenderTexture);

	//Target of where the portal is looking
	UFUNCTION(BlueprintPure, Category = "Portal")
	AActor* GetTarget();

	UFUNCTION(BlueprintCallable, Category = "Portal")
	void SetTarget(AActor* NewTarget);

	//Status of the Portal (being visualized by the player or not)
	UFUNCTION(BlueprintPure, Category = "Portal")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "Portal")
	void SetActive(bool NewActive);

	UFUNCTION(BlueprintCallable, Category = "Portal")
	virtual void TeleportActor(AActor* TeleportActor);


	//Math Calculation Functions about Converting Spaces
	FVector ConvertLocation(AActor* CurrentPortal, AActor* TargetPortal, FVector Location);
	FRotator ConvertRotation(AActor* CurrentPortal, AActor* TargetPortal, FRotator Rotation);
	FVector ConvertDirection(AActor* CurrentPortal, AActor* TargetPortal, FVector Direction);
	FVector ConvertVelocity(AActor* CurrentActor, AActor * TargetActor, FVector Velocity);
	

protected:

	//Change Scale Vertex Param of Dynamic Material

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Portal")
	UStaticMeshComponent* PortalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	UMaterialInterface* M_PortalMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* DM_PortalMesh;

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* PortalRootComponent;

	UPROPERTY()
	AActor* Target;

	UPROPERTY()
	AActor* ActorToTeleport;

	UPROPERTY()
	APawn* PlayerPawn;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	APlayerCameraManager* PlayerCameraManager;

	// Math Calculation Functions about Relationships between Point and Portal
	bool IsPointInFrontOfPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);
	bool IsPointCrossingPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);
	bool IsPointInsideBox(FVector Point, UBoxComponent* Box);
	bool IsPlayerLookTowardPortal(AActor* CurrentPortal);
	bool IsVelocityDirectTowardPortal(AActor* TeleportActor, AActor* CurrentPortal);
	bool IsCrossPortalNextFrame(AActor* TeleportActor, AActor* CurrentPortal);

	void SetScaleVertexParam(float Value);

private:

	bool bIsActive = false;

	void SetPortalMeshMaterial();

	//Used for Tracking movement of a point
	FVector LastPosition;
	bool LastInFront;



	// After Teleportation Changes
	void ChangePlayerVelocity(AActor* TeleportActor);
	void ChangeComponentsVelocity(AActor* TeleportActor);
	void ChangePlayerControlRotation(AActor* TeleportActor);
	void ChangePhysicsObjectRotationAndLocation(AActor* TeleportActor);
};
