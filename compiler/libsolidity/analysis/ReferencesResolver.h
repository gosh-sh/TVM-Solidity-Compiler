/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-3.0
/**
 * @author Christian <c@ethdev.com>
 * @date 2014
 * Component that resolves type names to types and annotates the AST accordingly.
 */

#pragma once

#include <libsolidity/ast/ASTVisitor.h>
#include <libsolidity/ast/ASTAnnotations.h>
#include <liblangutil/EVMVersion.h>

#include <list>
#include <map>

namespace solidity::langutil
{
class ErrorReporter;
struct SourceLocation;
}

namespace solidity::frontend
{

class NameAndTypeResolver;

/**
 * Resolves references to declarations (of variables and types) and also establishes the link
 * between a return statement and the return parameter list.
 */
class ReferencesResolver: private ASTConstVisitor
{
public:
	ReferencesResolver(
		langutil::ErrorReporter& _errorReporter,
		NameAndTypeResolver& _resolver,
		langutil::EVMVersion _evmVersion,
		bool _resolveInsideCode = false
	):
		m_errorReporter(_errorReporter),
		m_resolver(_resolver),
		m_evmVersion(_evmVersion),
		m_resolveInsideCode(_resolveInsideCode)
	{}

	/// @returns true if no errors during resolving and throws exceptions on fatal errors.
	bool resolve(ASTNode const& _root);

private:
	bool visit(Block const& _block) override;
	void endVisit(Block const& _block) override;
	bool visit(TryCatchClause const& _tryCatchClause) override;
	void endVisit(TryCatchClause const& _tryCatchClause) override;
	bool visit(ForStatement const& _for) override;
	bool visit(ForEachStatement const& _for) override;
	void endVisit(ForStatement const& _for) override;
	void endVisit(ForEachStatement const& _for) override;
	void endVisit(VariableDeclarationStatement const& _varDeclStatement) override;
	bool visit(VariableDeclaration const& _varDecl) override;
	bool visit(Identifier const& _identifier) override;
	bool visit(FunctionDefinition const& _functionDefinition) override;
	void endVisit(FunctionDefinition const& _functionDefinition) override;
	bool visit(ModifierDefinition const& _modifierDefinition) override;
	void endVisit(ModifierDefinition const& _modifierDefinition) override;
	void endVisit(IdentifierPath const& _path) override;
	bool visit(InlineAssembly const& _inlineAssembly) override;
	bool visit(Return const& _return) override;

	void resolveInheritDoc(StructuredDocumentation const& _documentation, StructurallyDocumentedAnnotation& _annotation);

	langutil::ErrorReporter& m_errorReporter;
	NameAndTypeResolver& m_resolver;
	langutil::EVMVersion m_evmVersion;
	/// Stack of return parameters.
	std::vector<ParameterList const*> m_returnParameters;
	bool const m_resolveInsideCode;
};

}
