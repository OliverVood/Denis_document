<?php

	namespace Base\Editor;

	require 'views/select.tpl';
	require 'views/create.tpl';
	require 'views/update.tpl';

	use Base\DB\Table;
	use JetBrains\PhpStorm\NoReturn;

	use Base\Controller;
	use Base\Action;
	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;

	abstract class Editor {
		protected string $name;
		protected array $params;
		protected Table $table;

		public Action $select;
		public Action $create;
		public Action $update;
		public Action $delete;

		public Action $do_create;
		public Action $do_update;
		public Action $do_delete;

		public bool $controlUpdate = true;
		public bool $controlDelete = true;

		public string $titleSelect = 'Выборка';
		protected string $titleCreate = 'Создание';
		protected string $titleUpdate = 'Редактирование';
		protected string $titleDelete = 'Удалить?';
//		protected string $titleView = 'Просмотр';

		protected string $titleDoCreate = 'Создано';
		protected string $titleDoUpdate = 'Изменено';
		protected string $titleDoDelete = 'Удалено';

		protected function __construct(string $name, Table $table, array $params = []) {
			$this->name = $name;
			$this->params = $params;
			$this->table = $table;

			$this->select = new Action($this->name, 'select', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/select', Admin.General.Render.ToMain); return false;");
			$this->create = new Action($this->name, 'create', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/create', Admin.General.Render.ToMain); return false;");
			$this->update = new Action($this->name, 'update', 'default', /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {id: %id%}, Admin.General.Render.ToMain); return false;");
//			$this->delete = new Action($this->name, 'delete', 'default', /* @lang JavaScript */"if (confirm({$this->titleDelete})) Base.Common.Query.SendData('/{$this->name}/delete', {id: %id%}, Admin.General.Render.ToMain); return false;");

			$this->do_create = new Action($this->name, 'do_create', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, Admin.General.Render.ToMain); return false;");
			$this->do_update = new Action($this->name, 'do_update', "/{$this->name}/do_update?id=%id%", /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, Admin.General.Render.ToMain); return false;");
			$this->do_delete = new Action($this->name, 'do_delete', "/{$this->name}/do_delete?id=%id%", /* @lang JavaScript */ "if (confirm('{$this->titleDelete}')) Base.Common.Query.SendData('/{$this->name}/do_delete', {id: %id%}, Admin.General.Render.ToMain); return false;");

			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
		}

		protected function Select():string {
			$where = isset($this->params['where']) ? implode(', ', $this->params['where']) : null;
			$order = isset($this->params['order']) ? implode(', ', $this->params['order']) : null;

			$result = $this->table->Select(null, $where, $order);
			$items = $this->table->FetchAll($result, function(& $items, $item) {
				$items[] = $item;
			});

			return Select::object()->ToVar($this, $this->params['select'] ?? [], $items, $this->titleSelect);
		}

		#[NoReturn] public function OnSelect(): void {
			SendJSONSuccess(['html' => $this->Select()]);
		}

		#[NoReturn] public function OnCreate(): void {
			SendJSONSuccess(['html' => Create::object()->ToVar($this, $this->params['create'] ?? [], [], $this->titleCreate)]);
		}

		#[NoReturn] public function OnUpdate(): void {
			$id = (int)GetParam('id', 0);
			$result = $this->table->Select(null, "(`id` = {$id})");
			$item = $this->table->Fetch($result);
			$data = [];

			$this->PrepareOnUpdate($id, $item, $data);
			SendJSONSuccess(['html' => Update::object()->ToVar($this, $id, $this->params['update'] ?? [], $item, $data, $this->titleUpdate)]);
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

			$this->table->Insert($data);

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = (int)GetParam('id', 0);
			$data = GetParam('form', []);

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoDelete(): void {
			$id = (int)GetParam('id', 0);

			$this->table->Update(['state' => 100], "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoDelete, 'html' => $this->Select()]);
		}

		protected function PrepareOnUpdate(int $id, array & $item, array & $data): void { }

	}