<?php

	namespace Base\Editor;

	require 'views/select.tpl';
	require 'views/create.tpl';
	require 'views/update.tpl';

	use JetBrains\PhpStorm\NoReturn;

	use Base\Controller;
	use Base\Action;
	use Base\DB\Table;
	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;

	abstract class Editor {
		protected string $name;
		protected Table $table;

		public Action $select;
		public Action $create;
		public Action $update;
		public Action $delete;

		public Action $do_create;
		public Action $do_update;
		public Action $do_delete;

		public array $navigateSelect = [];
		public array $navigateCreate = [];
		public array $navigateUpdate = [];

		public array $manage = [];

		public array $params = [];

		protected array $where = [];
		protected array $order = [];

		protected array $fieldsSelect = [];
		protected array $fieldsCreate = [];
		protected array $fieldsUpdate = [];

		protected string $titleSelect = 'Выборка';
		protected string $titleCreate = 'Создание';
		protected string $titleUpdate = 'Редактирование';
		protected string $titleDelete = 'Удалить?';
		protected string $titleView = 'Просмотр';

		protected string $titleDoCreate = 'Создано';
		protected string $titleDoUpdate = 'Изменено';
		protected string $titleDoDelete = 'Удалено';

		protected function __construct(string $name, Table $table) {
			$this->name = $name;
			$this->table = $table;

			$this->GetParams();

			$this->SetWhere($this->params);
			$this->SetOrder();

			$this->RegTitles();

			$this->SetFields($this->params);

			$this->RegActions();
			$this->SetHandlers();

			$this->SetNavigates();
			$this->SetManage();
		}

		protected function RegActions(): void {
			$this->RegActionSelect();
			$this->RegActionCreate();
			$this->RegActionUpdate();
			$this->RegActionDelete();

			$this->RegActionDoCreate();
			$this->RegActionDoUpdate();
			$this->RegActionDoDelete();
		}

		protected function RegActionSelect(): void { $this->select = new Action($this->name, 'select', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/select', Admin.General.Render.ToMain); return false;"); }
		protected function RegActionCreate(): void { $this->create = new Action($this->name, 'create', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/create', Admin.General.Render.ToMain); return false;"); }
		protected function RegActionUpdate(): void { $this->update = new Action($this->name, 'update', "/{$this->name}/update?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {id: %id%}, Admin.General.Render.ToMain); return false;"); }
		protected function RegActionDelete(): void { /* $this->delete = new Action($this->name, 'delete', "/{$this->name}/delete?id=%id", /* @lang JavaScript * /"if (confirm({$this->titleDelete})) Base.Common.Query.SendData('/{$this->name}/delete', {id: %id%}, Admin.General.Render.ToMain); return false;"); */ }

		protected function RegActionDoCreate(): void { $this->do_create = new Action($this->name, 'do_create', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, Admin.General.Render.ToMain); return false;"); }
		protected function RegActionDoUpdate(): void { $this->do_update = new Action($this->name, 'do_update', "/{$this->name}/do_update?id=%id%", /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, Admin.General.Render.ToMain); return false;"); }
		protected function RegActionDoDelete(): void { $this->do_delete = new Action($this->name, 'do_delete', "/{$this->name}/do_delete?id=%id%", /* @lang JavaScript */ "if (confirm('{$this->titleDelete}')) Base.Common.Query.SendData('/{$this->name}/do_delete', {id: %id%}, Admin.General.Render.ToMain); return false;"); }

		protected function SetHandlers(): void {
			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
			Controller::instance()->view->Push($this->do_update, [$this, 'DoUpdate']);
			Controller::instance()->view->Push($this->do_delete, [$this, 'DoDelete']);
		}

		protected function GetParams(): void { $this->params = $this->Params(); }
		protected function Params(): array { return []; }

		protected function SetWhere(array $params): void { $this->where = $this->Where($params); }
		protected function Where(array $params): array { return []; }

		protected function SetOrder(): void { $this->order = $this->Order(); }
		protected function Order(): array { return []; }

		protected function SetFields(array $params): void {
			$this->fieldsSelect = $this->FieldsSelect($params);
			$this->fieldsCreate = $this->FieldsCreate($params);
			$this->fieldsUpdate = $this->FieldsUpdate($params);
		}

		protected function FieldsSelect(array $params): array { return []; }
		protected function FieldsCreate(array $params): array { return []; }
		protected function FieldsUpdate(array $params): array { return []; }

		protected function RegTitles(): void {  }

		protected function SetNavigates(): void {
			$this->navigateSelect = $this->NavigateSelect();
			$this->navigateCreate = $this->NavigateCreate();
			$this->navigateUpdate = $this->NavigateUpdate();
		}

		protected function NavigateSelect(): array { return []; }
		protected function NavigateCreate(): array { return [ function (array $params) { return $this->select->GetLink("<< {$this->titleSelect}"); } ]; }
		protected function NavigateUpdate(): array { return [ function (array $params) { return $this->select->GetLink("<< {$this->titleSelect}"); } ]; }

		protected function SetManage(): void {
			$this->manage = $this->Manage();
		}

		protected function Manage(): array {
			return [
				function (array $params, array $item) { return $this->update->GetLink('Изменить', ['id' => $item['id']]); },
				function (array $params, array $item) { return $this->do_delete->GetLink('Удалить', ['id' => $item['id']]); }
			];
		}

		protected function Select():string {
			$where = ($this->where) ? implode(' AND ', $this->where) : null;
			$order = ($this->order) ? implode(', ', $this->order) : null;

			$result = $this->table->Select(null, $where, $order);
			$items = $this->table->FetchAll($result, function(& $items, $item) {
				$items[] = $item;
			});

			return Select::object()->ToVar($this, $this->fieldsSelect, $items, $this->titleSelect);
		}

		#[NoReturn] public function OnSelect(): void {
			SendJSONSuccess(['html' => $this->Select()]);
		}

		#[NoReturn] public function OnCreate(): void {
			SendJSONSuccess(['html' => Create::object()->ToVar($this, $this->fieldsCreate, [], $this->titleCreate)]);
		}

		#[NoReturn] public function OnUpdate(): void {
			$id = GetInt('id');
			$result = $this->table->Select(null, "(`id` = {$id})");
			$item = $this->table->Fetch($result);
			$data = [];

			$this->PrepareOnUpdate($id, $item, $data);
			SendJSONSuccess(['html' => Update::object()->ToVar($this, $id, $this->fieldsUpdate, $item, $data, $this->titleUpdate)]);
		}

		#[NoReturn] public function DoCreate(): void {
			$data = GetParam('form', []);

			$this->table->Insert($data);

			SendJSONSuccess(['message' => $this->titleDoCreate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoUpdate(): void {
			$id = GetInt('id');
			$data = GetParam('form', []);

			$this->table->Update($data, "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoUpdate, 'html' => $this->Select()]);
		}

		#[NoReturn] public function DoDelete(): void {
			$id = GetInt('id');

			$this->table->Update(['state' => 100], "`id` = {$id}");

			SendJSONSuccess(['message' => $this->titleDoDelete, 'html' => $this->Select()]);
		}

		protected function PrepareOnUpdate(int $id, array & $item, array & $data): void { }
		protected function PrepareOnSelect(int $id, array & $item, array & $data): void { }

	}