<?php

	namespace Base\Editor;

	require DIR_BASE . 'editor/editor.basic.inc';

	use Base\Action;

	abstract class Actions extends Basic {
		protected string $name;

		public Action $select;
		public Action $browse;
		public Action $create;
		public Action $update;
		public Action $delete;

		public Action $do_create;
		public Action $do_update;
		public Action $do_delete;
		public Action $set_state;

		protected function __construct(string $name) {
			parent::__construct($name);

			$this->RegActions();
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

	}