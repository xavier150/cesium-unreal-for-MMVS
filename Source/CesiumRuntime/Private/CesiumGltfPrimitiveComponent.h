// Copyright 2020-2026 CesiumGS, Inc. and Contributors

#pragma once

#include "CesiumPrimitive.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Engine/StaticMesh.h"

#include "CesiumGltfPrimitiveComponent.generated.h"

/**
 * A component that represents and renders a glTF mesh primitive made
 * from triangles.
 */
UCLASS()
class UCesiumGltfPrimitiveComponent : public UStaticMeshComponent,
                                      public ICesiumPrimitive {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UCesiumGltfPrimitiveComponent();
  virtual ~UCesiumGltfPrimitiveComponent();

  void BeginDestroy() override;

  FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

  // from ICesiumPrimitive
  CesiumPrimitiveData& getPrimitiveData() override;
  const CesiumPrimitiveData& getPrimitiveData() const override;
  void
  UpdateTransformFromCesium(const glm::dmat4& CesiumToUnrealTransform) override;

  // from ICesiumLoadedTilePrimitive
  ICesiumLoadedTile& GetLoadedTile() override;
  UStaticMeshComponent& GetMeshComponent() override;
  std::optional<uint32_t> FindTextureCoordinateIndexForGltfAccessor(
      int32_t accessorIndex) const override;

  virtual void OnCreatePhysicsState() override;

private:
  CesiumPrimitiveData _cesiumData;

public:
  // Bound Custom Offset
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag|CesiumOverride")
  FVector BoundCustomOffset = FVector(0.0f, 0.0f, 0.0f);

  // Bound Custom Extend
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tag|CesiumOverride")
  FVector BoundCustomExtend = FVector(0.0f, 0.0f, 0.0f);

  // Set custom bound
  UFUNCTION(BlueprintCallable, Category = "Tag|CesiumOverride")
  void SetCesiumBoundOverride(FVector CustomOffset, FVector CustomExtend) {
    BoundCustomOffset = CustomOffset;
    BoundCustomExtend = CustomExtend;
  }

  /* CESIUM OVERRIDE NOTES:
   * Add custom bounds for CesiumGltfPrimitiveComponent
   * Added BoundCustomOffset and BoundCustomExtend properties,
   * and SetCesiumBoundOverride function to allow for custom bounding box overrides.
   */
};
