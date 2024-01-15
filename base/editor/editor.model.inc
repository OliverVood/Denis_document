<?php

	namespace Base\Editor;

	use Base\DB\Table;

	class Model {
		protected Table $table;
		protected array $states;
		protected array $params;

		public function __construct(Table $table, array $params = []) {
			$this->table = $table;
			$this->params = $params;

			$this->Init();
		}

		protected function Init(): void {
			$this->states = [];
		}

		public function AccessState(int $from, int $to): bool {
			return (!isset($this->states[$from]) || !in_array($to, $this->states[$from]));
		}

		public function SelectData(int $page_current = 1, int $page_entries = 0): array {
			$query = $this->querySelect->get();

			$ext = [];
			if ($page_entries) {
				$start = ($page_current - 1) * $page_entries;
				$result = $this->table->Query("SELECT COUNT(*) AS `count` FROM ({$query}) AS `table`");
				$page_records = $this->table->Fetch($result)['count'];

				$ext['page'] = [
					'records' => $page_records,
					'current' => $page_current,
					'count' => (int)ceil($page_records / $page_entries)
				];
				$query = $this->querySelect->limit($start, $page_entries)->get();
			}

			$result = $this->table->Query($query);
			$items = $this->table->FetchAll($result, function(& $items, $item) {
				$items[] = $item;
			});

			return [$items, $ext];
		}

		public function GetItem(int $id): array {
			return $this->table->SelectOne(null, "(`id` = {$id})");
		}

		public function GetState(int $id): int {
			return (int)$this->table->SelectOneField('state', "`id` = {$id}");
		}

		protected function PrepareCreate(array & $data): void {  }
		protected function PrepareUpdate(array & $data, int $id): void {  }
		protected function PrepareDelete(int $id): void {  }
		protected function PrepareSetState(int & $state, int $id): void {  }

		public function Create(array $data): void {
			$this->PrepareCreate($data);
			$this->table->Insert($data);
		}

		public function Update(array $data, int $id): void {
			$this->PrepareUpdate($data, $id);
			$this->table->Update($data, "`id` = {$id}");
		}

		public function Delete(int $id): void {
			$this->PrepareDelete($id);
			$this->table->Update(['state' => 100], "`id` = {$id}");
		}

		public function SetState(int $state, int $id): void {
			$this->PrepareSetState($state, $id);
			$this->table->Update(['state' => $state], "`id` = {$id}");
		}

	}