// This file is part of Wintermute Engine
// For conditions of distribution and use, see copyright notice in license.txt

#ifndef __ArmedSceneNodeModel_H__
#define __ArmedSceneNodeModel_H__


#include <QAbstractItemModel>
#include "Scene3DBase.h"

using namespace Wme;

namespace Wme
{
	class MeshEntity;
}

namespace Armed
{
	class DocScene;
	class SceneNode;	

	class SceneNodeModel : public QAbstractItemModel, Wme::Scene3DBase::SceneGraphListener
	{
		Q_OBJECT

	public:
		SceneNodeModel(QObject* parent);
		~SceneNodeModel();

		enum Column { Name, Type };

		void SetScene(DocScene* scene);

		SceneNode* NodeForIndex(const QModelIndex& index) const;
		QModelIndex IndexFromNode(SceneNode* node) const;
		QModelIndex IndexFromNode(Ogre::SceneNode* node) const;

		Ogre::SceneNode* GetRealRootNode() const;
		SceneNode* GetRootNode() const { return m_RootNode; }

		void RegisterNode(SceneNode* node, Ogre::SceneNode* ogreNode);
		void UnregisterNode(Ogre::SceneNode* ogreNode);
		void RebuildNodeIndex();

		// QAbstractItemModel
		Qt::ItemFlags flags(const QModelIndex& index) const;
		QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		int rowCount(const QModelIndex& parent = QModelIndex()) const;
		int columnCount(const QModelIndex& parent = QModelIndex()) const;
		QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex& index) const;

		Qt::DropActions supportedDragActions() const { return Qt::MoveAction; }
		Qt::DropActions supportedDropActions() const { return Qt::MoveAction; }
		QStringList mimeTypes() const;
		QMimeData* mimeData(const QModelIndexList& indexes) const;
		bool dropMimeData(const QMimeData* mimeData, Qt::DropAction action, int row, int column, const QModelIndex& parent);

		// Wme::Scene3DBase::SceneGraphListener
		void OnSceneNodeAdded(Ogre::SceneNode* node);
		void OnSceneNodeRemoving(Ogre::SceneNode* node);
		void OnSceneNodeChanged(Ogre::SceneNode* node);
		void OnSceneGraphDirty();

	signals:
		void IndexesDropped(const QModelIndexList& indexList);

	public slots:
		void RefreshAll();

	private slots:
		void SelectItemsAfterDrop();

	private:
		DocScene* m_Scene;
		SceneNode* m_RootNode;

		static const int ColumnCount = 1;
		static const QString MimeType;
		
		void BuildSceneTree();
		void PopulateNode(SceneNode* parentNode, Ogre::SceneNode* ogreSceneNode);
		void PopulateNode(SceneNode* parentNode, MeshEntity* meshEntity, Ogre::Bone* bone);
		SceneNode* AddChildNode(SceneNode* parentNode, Ogre::SceneNode* ogreSceneNode);
		void AddBones(SceneNode* parentNode);

		QMap<Ogre::SceneNode*, SceneNode*> m_NodeMap;

		QList<SceneNode*> m_DroppedNodes;

		bool m_DropInProgress;
		bool m_IsDirty;

	};
}

#endif // __ArmedSceneNodeModel_H__
