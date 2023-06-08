<?php

	namespace Proj\Admin\Editor\HTML;

	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.model.inc';

	use Base\EditorMySQLi\HTML\Editor;;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Units\HTML as Units;
	use Proj\Admin\Editor\Model;

	class Changes extends Editor {
		use Model\Changes;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHref('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHref('Удалить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return Units\Changes::instance()->editor_change->select->GetLinkHref('Список', array_merge(['cid' => $item['id'], 'page' => 1], $this->params)); }
			];
		}

	}