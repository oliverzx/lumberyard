/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#include "LmbrCentral_precompiled.h"
#include "LmbrCentralEditor.h"
#include "LmbrCentralReflectionTest.h"
#include "Shape/EditorCapsuleShapeComponent.h"
#include <AzToolsFramework/Application/ToolsApplication.h>

namespace LmbrCentral
{
    // Serialized legacy EditorCapsuleShapeComponent v1.
    const char kEditorCapsuleComponentVersion1[] =
        R"DELIMITER(<ObjectStream version="1">
        <Class name="EditorCapsuleShapeComponent" field="element" version="1" type="{06B6C9BE-3648-4DA2-9892-755636EF6E19}">
            <Class name="EditorComponentBase" field="BaseClass1" version="1" type="{D5346BD4-7F20-444E-B370-327ACD03D4A0}">
                <Class name="AZ::Component" field="BaseClass1" type="{EDFCB2CF-F75D-43BE-B26B-F35821B29247}">
                    <Class name="AZ::u64" field="Id" value="10467239283436660413" type="{D6597933-47CD-4FC8-B911-63F3E2B0993A}"/>
                </Class>
            </Class>
            <Class name="CapsuleShapeConfig" field="Configuration" version="1" type="{00931AEB-2AD8-42CE-B1DC-FA4332F51501}">
                <Class name="float" field="Height" value="0.5700000" type="{EA2C3E90-AFBE-44D4-A90D-FAAF79BAF93D}"/>
                <Class name="float" field="Radius" value="1.5700000" type="{EA2C3E90-AFBE-44D4-A90D-FAAF79BAF93D}"/>
            </Class>
        </Class>
    </ObjectStream>)DELIMITER";

    class LoadEditorCapsuleShapeComponentFromVersion1
        : public LoadReflectedObjectTest<AZ::ComponentApplication, LmbrCentralEditorModule, EditorCapsuleShapeComponent>
    {
    protected:
        const char* GetSourceDataBuffer() const override { return kEditorCapsuleComponentVersion1; }

        void SetUp() override
        {
            LoadReflectedObjectTest::SetUp();

            if (m_object)
            {
                m_editorCapsuleShapeComponent = m_object.get();
                m_CapsuleShapeConfig = m_editorCapsuleShapeComponent->GetConfiguration();
            }
        }

        EditorCapsuleShapeComponent* m_editorCapsuleShapeComponent = nullptr;
        CapsuleShapeConfig m_CapsuleShapeConfig;

    };

    TEST_F(LoadEditorCapsuleShapeComponentFromVersion1, Application_IsRunning)
    {
        ASSERT_NE(GetApplication(), nullptr);
    }

    TEST_F(LoadEditorCapsuleShapeComponentFromVersion1, Components_Load)
    {
        EXPECT_NE(m_object.get(), nullptr);
    }

    TEST_F(LoadEditorCapsuleShapeComponentFromVersion1, EditorComponent_Found)
    {
        EXPECT_NE(m_editorCapsuleShapeComponent, nullptr);
    }

    TEST_F(LoadEditorCapsuleShapeComponentFromVersion1, Height_MatchesSourceData)
    {
        EXPECT_FLOAT_EQ(m_CapsuleShapeConfig.m_height, 0.57f);
    }

    TEST_F(LoadEditorCapsuleShapeComponentFromVersion1, Radius_MatchesSourceData)
    {
        EXPECT_FLOAT_EQ(m_CapsuleShapeConfig.m_radius, 1.57f);
    }
}

