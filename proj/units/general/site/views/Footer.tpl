<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;
	use Proj\Site\Units\Feedback;
	use Proj\Site\Units\General;
	use Proj\Site\Params;

	class Footer extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render(): void { ?>
			<div class = "view general footer">
				<div>
					<div class = "agency">
						<div class = "logo"><?= General::instance()->home->GetLink(''); ?></div>
						<div class = "info">
							<div class = "name"><?= Params::$site_name; ?></div>
							<div class = "slogan">управляй своими документами</div>
						</div>
					</div>
					<div class = "menu">
						<div><?= Feedback::instance()->feedback->GetLink('Обратная связь'); ?></div>
						<div><?= General::instance()->donations->GetLink('Поддержать проект'); ?></div>
						<div><?= General::instance()->privacy_policy->GetLink('Политика конфиденциальности'); ?></div>
						<div><?= General::instance()->terms_use->GetLink('Пользовательское соглашение'); ?></div>
					</div>
				</div>
			</div>
		<?php }

	}