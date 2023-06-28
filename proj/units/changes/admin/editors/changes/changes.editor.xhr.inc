<?php

	namespace Proj\Admin\Editor\XHR;

	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.common.inc';
	require DIR_UNITS . 'changes/admin/editors/changes/changes.editor.model.inc';

	use Base\Editor\MySQLi\XHR\Editor;
	use Base\DB\MySQLi\Table;
	use Proj\Admin\Editor\Common;
	use Proj\Admin\Editor\Model;
	use Proj\Admin\Units\XHR as Units;

	class Changes extends Editor {
		use Common\Changes;

		public function __construct(string $name, Table $table) {
			parent::__construct($name);

			$this->model = new Model\Changes($table);

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