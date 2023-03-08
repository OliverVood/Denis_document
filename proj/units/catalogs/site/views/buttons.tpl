<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;
	use Proj\Site\Units\Catalogs;

	class Buttons extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render(): void { ?>
			<div class = "view catalogs buttons">
				<div class = "grid col_1">
					<div>
						<h1>Начните работу прямо сейчас</h1>
					</div>
				</div>
				<div class = "btns">
					<?= Catalogs::instance()->action_estimate->GetLink('Сметы »', [], ['class' => 'button']); ?>
					<?= Catalogs::instance()->action_certificate->GetLink('Акты выполненных работ »', [], ['class' => 'button']); ?>
					<?= Catalogs::instance()->action_price_list->GetLink('Прайс-листы »', [], ['class' => 'button']); ?>
				</div>
			</div>
		<?php }

	}