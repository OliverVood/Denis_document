<?php

	namespace Base\Editor;

	require DIR_BASE . 'editor/skins/skin.inc';

	require DIR_BASE . 'editor/views/select.tpl';
	require DIR_BASE . 'editor/views/create.tpl';
	require DIR_BASE . 'editor/views/update.tpl';
	require DIR_BASE . 'editor/views/browse.tpl';

	use Base\Action;
	use Base\DB\Table;
	use Base\DB\Select;
	use Base\Pages;

	abstract class Editor {
		protected string $name;
		protected Table $table;
		protected Select $querySelect;

		public Action $select;
		public Action $browse;
		public Action $create;
		public Action $update;
		public Action $delete;

		public Action $do_create;
		public Action $do_update;
		public Action $do_delete;
		public Action $set_state;

		protected string $titleSelect = 'Выборка';
		protected string $titleBrowse = 'Просмотр';
		protected string $titleCreate = 'Создание';
		protected string $titleUpdate = 'Редактирование';
		protected string $titleDelete = 'Удалить?';
		protected string $titleState = 'Изменить состояние?';

		protected string $titleDoCreate = 'Создано';
		protected string $titleDoUpdate = 'Изменено';
		protected string $titleDoDelete = 'Удалено';
		protected string $titleSetState = 'Состояние изменено';

		protected string $errorAccess = 'Доступ запрещён';

		protected array $states	= [];

		protected array $params = [];

		protected array $manageSelect = [];

		protected int $page_entries = 10;

		protected function __construct(string $name, Table $table) {
			$this->name = $name;
			$this->table = $table;

			$this->RegActions();
			$this->SetHandlers();
		}

		protected function RegActionSelect(): void { $this->select = new Action($this->name, 'select', "/{$this->name}/select?page=%page%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/select', {page: %page%}); return false;"); }
		protected function RegActionBrowse(): void { $this->browse = new Action($this->name, 'browse', "/{$this->name}/browse?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/browse', {id: %id%}); return false;"); }
		protected function RegActionCreate(): void { $this->create = new Action($this->name, 'create', 'default', /* @lang JavaScript */"Base.Common.Query.Send('/{$this->name}/create'); return false;"); }
		protected function RegActionUpdate(): void { $this->update = new Action($this->name, 'update', "/{$this->name}/update?id=%id%", /* @lang JavaScript */"Base.Common.Query.SendData('/{$this->name}/update', {id: %id%}); return false;"); }
//		protected function RegActionDelete(): void { $this->delete = new Action($this->name, 'delete', "/{$this->name}/delete?id=%id", /* @lang JavaScript */ "if (confirm({$this->titleDelete})) Base.Common.Query.SendData('/{$this->name}/delete', {id: %id%}); return false;"); }

		protected function RegActionDoCreate(): void { $this->do_create = new Action($this->name, 'do_create', 'default', /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this); return false;"); }
		protected function RegActionDoUpdate(): void { $this->do_update = new Action($this->name, 'do_update', "/{$this->name}/do_update?id=%id%", /* @lang JavaScript */ "Base.Common.Query.SubmitForm(this); return false;"); }
		protected function RegActionDoDelete(): void { $this->do_delete = new Action($this->name, 'do_delete', "/{$this->name}/do_delete?id=%id%", /* @lang JavaScript */ "if (confirm('{$this->titleDelete}')) Base.Common.Query.SendData('/{$this->name}/do_delete', {id: %id%}); return false;"); }
		protected function RegActionSetState(): void { $this->set_state = new Action($this->name, 'set_state', "/{$this->name}/set_state?id=%id%&state=%state%", /* @lang JavaScript */ "if (confirm('{$this->titleState}')) Base.Common.Query.SendData('/{$this->name}/set_state', {id: %id%, state: %state%}); return false;"); }

		protected function RegActions(): void {
			$this->RegActionSelect();
			$this->RegActionCreate();
			$this->RegActionUpdate();
//			$this->RegActionDelete();
			$this->RegActionBrowse();

			$this->RegActionDoCreate();
			$this->RegActionDoUpdate();
			$this->RegActionDoDelete();
			$this->RegActionSetState();
		}

		abstract protected function SetHandlers(): void;

		abstract protected function OnSelect(): void;
		abstract protected function OnBrowse(): void;
		abstract protected function OnCreate(): void;
		abstract protected function OnUpdate(): void;

		protected function selectQuery(): string {
			return $this->querySelect->calc('*')->table($this->table->GetName())->get();
		}

		protected function SelectData(): array {
			$query = $this->selectQuery();

			$ext = [];
			if ($this->page_entries) {
				$page_current = GetInt('page', 1);
				$start = ($page_current - 1) * $this->page_entries;
				$result = $this->table->Query("SELECT COUNT(*) AS `count` FROM ({$query}) AS `table`");
				$page_records = $this->table->Fetch($result)['count'];

				$ext['page'] = [
					'records' => $page_records,
					'current' => $page_current,
					'count' => (int)ceil($page_records / $this->page_entries)
				];
				$query = $this->querySelect->limit($start, $this->page_entries)->get();
			}

			$result = $this->table->Query($query);
			$items = $this->table->FetchAll($result, function(& $items, $item) {
				$items[] = $item;
			});

			return [$items, $ext];
		}

		protected function FieldsSelect(): array { return []; }
		protected function FieldsBrowse(): array { return []; }
		protected function FieldsCreate(): array { return []; }
		protected function FieldsUpdate(): array { return []; }

//		protected function PrepareOnSelect(array & $item): void { }
//		protected function PrepareOnBrowse(int $id, array & $item): void { }
//		protected function PrepareOnCreate(array & $item): void { }
//		protected function PrepareOnUpdate(int $id, array & $item): void { }

		protected function ManageSelect(): array {
			return [
				function (array $item) { return $this->update->GetLinkHref('Изменить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->do_delete->GetLinkHref('Удалить', array_merge(['id' => $item['id']], $this->params)); },
				function (array $item) { return $this->browse->GetLinkHref('Просмотреть', array_merge(['id' => $item['id']], $this->params)); }
			];
		}

		protected function NavigateSelect(): array { return []; }
		protected function NavigateBrowse(): array { return [ function () { return $this->select->GetLinkHref("<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }
		protected function NavigateCreate(): array { return [ function () { return $this->select->GetLinkHref("<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }
		protected function NavigateUpdate(): array { return [ function () { return $this->select->GetLinkHref("<< {$this->titleSelect}", array_merge(['page' => 1], $this->params)); } ]; }

		public function Pages($pages): string {
			if (!$this->page_entries) return '';

			return (new Pages($this->select, $pages['current'], $pages['count']))->ToString();
		}

	}