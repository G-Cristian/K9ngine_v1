#pragma once

#include <memory>
#include <vector>

namespace K9ngineCore {
  namespace K9Graphics {
    class ISceneGraphVisitor;
    class SceneGraph;

    class INode {
    public:
      using NodePtr = std::shared_ptr<INode>;
      friend SceneGraph;
    public:
      explicit INode(SceneGraph& sceneGraph);
      virtual ~INode() = default;

      virtual void accept(ISceneGraphVisitor&) = 0;

      const SceneGraph& getSceneGraph()const;
      SceneGraph& getSceneGraph();

      bool isDirty() const;

      const NodePtr getParent() const;
      NodePtr getParent();

      const std::vector<NodePtr>& getChildren() const;
    private:
      void cleanDirty();
      void setDirty();
    protected:
      std::vector<NodePtr> mChildren{};
      NodePtr mParent{ nullptr };
      SceneGraph& mSceneGraph;
      bool mIsDirty{ false };
    };
  }
}