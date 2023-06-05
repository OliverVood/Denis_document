<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.model.inc';

	use Base\Editor\XHR\EditorMySQLi;
	use Base\DB\TableMySQLi;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units\XHR as Units;

	class Changes extends EditorMySQLi {
		use Model\Changes;

		public function __construct(string $name, TableMySQLi $table) {
			parent::__construct($name, $table);

			$this->Init();

			$this->titleDoCreate = 'Список актуального добавлен';
			$this->titleDoUpdate = 'Список актуального изменён';
			$this->titleDoDelete = 'Список актуального удалён';
		}

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHref('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHref('Удалить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return Units\Changes::instance()->editor_change->select->GetLinkHref('Список', array_merge(['cid' => $item['id'], 'page' => 1], $this->params)); }
			];
		}

	}