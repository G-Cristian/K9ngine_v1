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
      using WeakNodePtr = std::weak_ptr<INode>;

      friend SceneGraph;
    public:
      explicit INode(SceneGraph& sceneGraph);
      INode(INode&&) noexcept;

      virtual ~INode();

      virtual void accept(ISceneGraphVisitor&) = 0;

      const SceneGraph& getSceneGraph()const;
      SceneGraph& getSceneGraph();

      bool isDirty() const;

      const NodePtr getParent() const;
      NodePtr getParent();

      const std::vector<NodePtr>& getChildren() const;
    private:
      INode(const INode&) = delete;
      INode& operator=(const INode&) = delete;
      INode& operator=(INode&&) noexcept = delete;

      void cleanDirty();
      void setDirty();
      void addChild(NodePtr child);
      void setParent(NodePtr parent);
    protected:
      std::vector<NodePtr> mChildren{};
      WeakNodePtr mParent;
      SceneGraph& mSceneGraph;
      bool mIsDirty{ false };
    };
  }
}