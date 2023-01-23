<?php

	namespace Base;

	require 'views/select.tpl';
	require 'views/create.tpl';
	require 'views/update.tpl';

	use Base\DB\Table;
	use JetBrains\PhpStorm\NoReturn;

	use Base\Templates\Editor\Select;
	use Base\Templates\Editor\Create;
	use Base\Templates\Editor\Update;

	class Editor {
		protected string $name;
		protected array $params;
		protected Table $table;

		public Action $select;
		public Action $create;
		public Action $update;

		public Action $do_create;

		protected string $titleSelect;
		protected string $titleCreate;
		protected string $titleUpdate;
		protected string $titleView;

		protected function __construct(string $name, Table $table, array $params = []) {
			$this->name = $name;
			$this->params = $params;
			$this->table = $table;

			$this->titleSelect = $this->params['titles']['select'] ?? 'Выборка';
			$this->titleCreate = $this->params['titles']['create'] ?? 'Создание';
			$this->titleUpdate = $this->params['titles']['update'] ?? 'Редактирование';
			$this->titleView = $this->params['titles']['view'] ?? 'Просмотр';

			$this->select = new Action($this->name, 'select', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/select', Admin.General.Render.ToMain); return false;");
			$this->create = new Action($this->name, 'create', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/create', Admin.General.Render.ToMain); return false;");
			$this->update = new Action($this->name, 'update', 'default');

			$this->do_create = new Action($this->name, 'do_create', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this, (data) => { console.log(data); }); return false;");

			Controller::instance()->view->Push($this->select, [$this, 'OnSelect']);
			Controller::instance()->view->Push($this->create, [$this, 'OnCreate']);
			Controller::instance()->view->Push($this->update, [$this, 'OnUpdate']);

			Controller::instance()->view->Push($this->do_create, [$this, 'DoCreate']);
		}

		#[NoReturn] public function OnSelect(): void {
			$order = isset($this->params['order']) ? implode(', ', $this->params['order']) : null;

			$result = $this->table->Select(null, null, $order);
			$items = $this->table->FetchAll($result, function(& $items, $item) {
				$items[] = $item;
			});

			SendJSONSuccess(['html' => Select::object()->ToVar($this->params['select'] ?? [], $items, $this->titleSelect)]);
		}

		#[NoReturn] public function OnCreate() : void {
			SendJSONSuccess(['html' => Create::object()->ToVar($this->params['create'] ?? [], [], $this->titleCreate)]);
		}

		public function OnUpdate() : void {
			Update::object()->ToVar();
		}

		#[NoReturn] public function DoCreate(): void {
			SendJSONSuccess([]);
		}

	}